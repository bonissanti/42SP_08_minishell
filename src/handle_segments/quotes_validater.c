/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_validater.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:32:29 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/08 20:19:54 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	analyzing_quotes(t_hashtable *env, char **args)
{
	t_segment	*head;

	head = NULL;
	if (!even_close_quotes(*args))
	{
		ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
		g_global.to_exec = 2;
		return ;
	}
	handle_quotes(env, head, args);
}

size_t	even_close_quotes(char *str)
{
	t_quote_bool	state;

	if (!str)
		return (0);
	init_structs(&state, false, sizeof(t_quote_bool));
	while (*str)
	{
		if (*str == '\\' && !state.escape_next && !state.single_open)
			state.escape_next = true;
		else if (state.escape_next)
			state.escape_next = false;
		else if (*str == '\'' && !state.double_open)
			state.single_open = !state.single_open;
		else if ((*str == '\"' && !state.single_open) && (!state.escape_next
				|| state.escape_next))
			state.double_open = !state.double_open;
		str++;
	}
	return (!state.single_open && !state.double_open);
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
