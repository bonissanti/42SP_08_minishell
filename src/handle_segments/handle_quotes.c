/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:32:57 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/16 17:04:40 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"
#include "../include/segments.h"

static void	handle_quotes(t_lex *quote);
static void	char_between_quotes(t_lex *quote, t_segment **head, size_t *len);
static void	literal_string(t_lex *quote, size_t *len);
void	final_process(t_lex *quote, t_segment **head, char **args,
				size_t *len);

void	is_quotes(t_hashtable *env, char **args)
{
	t_lex		*quote;
	t_segment	*head;
	size_t		len;

	len = 0;
	head = NULL;
	quote = init_lex(env, *args);
	quote->state.space_dollar = check_dollar_space(*args);
	
	if (!even_close_quotes(*args))
	{
		ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
		free(quote->segment);
		free(quote);
		return ;
	}
	while (*(quote->ptr))
	{
		if ((*quote->ptr == '\'' && !quote->state.double_open)
			|| (*quote->ptr == '\"' && !quote->state.single_open))
			handle_quotes(quote);
		else if (*quote->ptr == '$' && (quote->state.double_open 
			|| (!quote->state.single_open && !quote->state.double_open)))
			expand_variable(quote, &head, &len);
		else if (quote->state.single_open || quote->state.double_open)
			char_between_quotes(quote, &head, &len);
		else
			literal_string(quote, &len);
		quote->ptr++;
	}
	check_handle_error(quote, args, 1);
	final_process(quote, &head, args, &len);
}

static void	handle_quotes(t_lex *quote)
{
	if (*quote->ptr == '\'' && !quote->state.double_open)
		quote->state.single_open = !quote->state.single_open;
	else if (*quote->ptr == '\"' && !quote->state.single_open)
		quote->state.double_open = !quote->state.double_open;
}

static void	char_between_quotes(t_lex *quote, t_segment **head, size_t *len)
{
	quote->segment[*len] = *(quote->ptr); // Add char to segment
	(*len)++;
	if (*(quote->ptr + 1) == '\'' || *(quote->ptr + 1) == '\"')
	{
		quote->segment[*len] = '\0';
		add_segments(head, quote->segment);
		*len = 0;
	}
}

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

void	final_process(t_lex *quote, t_segment **head, char **args,
		size_t *len)
{
	quote->segment[*len] = '\0';
	add_segments(head, quote->segment);
	free(quote->segment);
	free(quote);
	*args = join_segments(*head);
	for (int i = 0; args[i]; i++)
		printf("%s ", args[i]);
	printf("\n");
	free_segments(*head);
}