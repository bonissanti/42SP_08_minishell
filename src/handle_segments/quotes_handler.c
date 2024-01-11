/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:32:57 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/11 11:02:37 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		toggle_quote_state(t_lex *quote);
static void		char_between_quotes(t_lex *quote, t_segment **head,
					size_t *len);
static void		literal_string(t_lex *quote, size_t *len);
void			final_process(t_lex *quote, t_segment **head, char **args,
					size_t *len);

void	quotes(t_hashtable *env, t_segment *head, t_shell *shell, char **args)
{
	t_lex	*quote;
	size_t	len;

	len = 0;
	quote = init_lex(env, *args, shell);
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
			expand_var(quote, &head, shell, &len);
		else if (quote->state.single_open || quote->state.double_open)
			char_between_quotes(quote, &head, &len);
		else
			literal_string(quote, &len);
		quote->ptr++;
	}
	check_handle_error(quote, 1);
	final_process(quote, &head, args, &len);
}

static inline void	toggle_quote_state(t_lex *quote)
{
	if (*quote->ptr == '\'' && !quote->state.double_open)
		quote->state.single_open = !quote->state.single_open;
	else if (*quote->ptr == '\"' && !quote->state.single_open)
		quote->state.double_open = !quote->state.double_open;
}

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

void	final_process(t_lex *quote, t_segment **head, char **args, size_t *len)
{
	quote->segment[*len] = '\0';
	add_segments(head, quote->segment);
	free(quote->segment);
	free(quote);
	*args = join_segments(*head);
	free_segments(*head);
}
