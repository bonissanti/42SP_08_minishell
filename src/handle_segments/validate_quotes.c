/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:32:29 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/16 17:00:55 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"
#include "../include/segments.h"

size_t even_close_quotes(char *str);
void	error_close_quotes(t_lex *quote);

t_bool	check_handle_error(t_lex *quote, char **args, int i)
{
	if (i == 0)
	{
		if (!even_close_quotes(*args))
		{
			ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
			free(quote->segment);
			free(quote);
			return (true);
		}
	}
	else if (i == 1)
	{
		if (quote->state.single_open || quote->state.double_open)
			error_close_quotes(quote);
	}
	return (false);
}

size_t even_close_quotes(char *str) 
{
	size_t single_quotes;
	size_t double_quotes;
	t_bool is_squote_open;
	t_bool is_dquote_open;
	t_bool is_escape_next;

	single_quotes = 0;
	double_quotes = 0;
	is_squote_open = false;
	is_dquote_open = false;
	is_escape_next = false;
   	while (*str)
	{
		if (*str == '\\' && !is_escape_next)
			is_escape_next = true;
		else if (is_escape_next)
			is_escape_next = false;
		else if (*str == '\'' && !is_dquote_open)
		{
			single_quotes++;
			is_squote_open = !is_squote_open;
		}
		else if (*str == '\"' && !is_squote_open)
		{
			double_quotes++;
			is_dquote_open = !is_dquote_open;
		}
		str++;
	}
	return (single_quotes % 2 == 0 && double_quotes % 2 == 0);
}

void	error_close_quotes(t_lex *quote)
{
	ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
	free(quote->segment);
	return ;
}

t_bool	check_dollar_space(char *str)
{
	while (*str)
	{
		if (*str == '$')
		{
			if (is_whitespace(*(str + 1)))
				return (true);
		}
		str++;
	}
	return (false);
}