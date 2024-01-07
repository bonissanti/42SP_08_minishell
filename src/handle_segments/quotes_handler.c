/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:32:57 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/07 17:06:48 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		toggle_quote_state(t_lex *quote);
static void		char_between_quotes(t_lex *quote, t_segment **head,
					size_t *len);
static void		literal_string(t_lex *quote, size_t *len);
void			final_process(t_lex *quote, t_segment **head, char **args,
					size_t *len);

/**
 * Function: Handle_quotes
 * -----------------
 * This is the main function to handle the quotes. It iterates through the
 * arguments, and if it finds a quote, it toggles the quote state. If it finds
 * a '$' and the quote state is open, it calls the function expand_variable.
 * If the quote state is open, it calls the function char_between_quotes.
 * If the quote state is closed, it calls the function literal_string.
 * After iterating through the arguments, it calls the function final_process.
 *  
 * @param: *env: The hashtable that contains all the environment variables.
 * @param: *head: The head of the linked list that contains all the segments.
 * @param: **args: The array of arguments.
 * @var: *quote: The struct that contains all the information about the quotes.
 * @var: len: The counter for the number of characters in the segment.
 * 
 * @return: Returns nothing.
 *
 */

void	handle_quotes(t_hashtable *env, t_segment *head, char **args)
{
	t_lex	*quote;
	size_t	len;

	len = 0;
	quote = init_lex(env, *args);
	quote->state.space_dollar = check_dollar_space(*args);
	while (*(quote->ptr))
	{
		if ((*quote->ptr == '\'' && !quote->state.double_open)
			|| (*quote->ptr == '\"' && !quote->state.single_open))
			toggle_quote_state(quote);
		else if (*quote->ptr == '$' && (quote->ptr[1] == '\''
				|| quote->ptr[1] == '"' || quote->ptr[1] == '/'))
			literal_string(quote, &len);
		else if (*quote->ptr == '$' && (quote->state.double_open
				|| (!quote->state.single_open && !quote->state.double_open)))
			expand_variable(quote, &head, &len);
		else if (quote->state.single_open || quote->state.double_open)
			char_between_quotes(quote, &head, &len);
		else
			literal_string(quote, &len);
		quote->ptr++;
	}
	check_handle_error(quote, 1);
	final_process(quote, &head, args, &len);
}

/**
 * Function: Toggle_quote_state
 * -----------------
 * This function toggles the quote state. If the quote is a single quote and
 * the double quote state is not open, it toggles the single quote state.
 * If the quote is a double quote and the single quote state is not open,
 * it toggles the double quote state.
 *  
 * @param: *quote: The struct that contains all the information about 
 * 			the quotes.
 * @var: single_open: The boolean that represents the single quote state.
 * @var: double_open: The boolean that represents the double quote state.
 * 
 * @return: Returns nothing.
 *
 */

static inline void	toggle_quote_state(t_lex *quote)
{
	if (*quote->ptr == '\'' && !quote->state.double_open)
		quote->state.single_open = !quote->state.single_open;
	else if (*quote->ptr == '\"' && !quote->state.single_open)
		quote->state.double_open = !quote->state.double_open;
}

/**
 * Function: Char_between_quotes
 * -----------------
 * This function is used to handle the characters between quotes. It iterates
 * through the characters and adds them to the segment. If the next character
 * is a quote, aka the quote that will close the segment, it adds the segment
 * to the linked list and resets the counter. If the next character is not a
 * quote, it just adds the character to the segment. Note that segments are
 * strings that are between quotes, then after they are added to the linked
 * list, it's important to reset the counter for the next segment, this avoids
 * errors like repeating previous segments or memory gb_to_free.
 *   
 * @param: *quote: The struct that contains all the information about 
 * 			the quotes.
 * @var: **head: The head of the linked list that contains all the segments.
 * @var: len: The counter for the number of characters in the segment.
 * 
 * @return: Returns nothing.
 *
 */

static void	char_between_quotes(t_lex *quote, t_segment **head, size_t *len)
{
	quote->segment[*len] = *(quote->ptr);
	(*len)++;
	if (*(quote->ptr + 1) == '\'' || *(quote->ptr + 1) == '\"')
	{
		quote->segment[*len] = '\0';
		add_segments(head, quote->segment);
		*len = 0;
	}
}

/**
 * Function: Literal_string
 * -----------------
 * This function is used to handle the literal strings. It iterates through
 * the characters and adds them to the segment. If the next character is a
 * backslash, it adds the next character to the segment and increments the
 * counter. If the next character is not a backslash, it just adds the
 * character to the segment.
 * 
 * @param: *quote: The struct that contains all the information about 
 * 			the quotes.
 * @var: len: The counter for the number of characters in the segment.
 * 
 * @return: Returns nothing.
 *
 */

static void	literal_string(t_lex *quote, size_t *len)
{
	if (*quote->ptr == '\\')
	{
		quote->ptr++;
		quote->segment[*len] = *(quote->ptr);
		(*len)++;
	}
	else
	{
		quote->segment[*len] = *(quote->ptr);
		(*len)++;
	}
}

/**
 * Function: Final_process
 * -----------------
 * This function is used to finalize the process of handling the quotes. It
 * adds the last segment to the linked list, then it joins all the segments
 * into a single string. After that, it frees the segments and the struct.
 * @param: *quote: The struct that contains all the information about 
 * 			the quotes.
 * @param: **head: The head of the linked list that contains all the segments.
 * @param: **args: The array of arguments.
 * @param: len: The counter for the number of characters in the segment.
 * 
 * @return: Returns nothing.
 *
 */

void	final_process(t_lex *quote, t_segment **head, char **args, size_t *len)
{
	quote->segment[*len] = '\0';
	add_segments(head, quote->segment);
	free(quote->segment);
	free(quote);
	*args = join_segments(*head);
	free_segments(*head);
}
