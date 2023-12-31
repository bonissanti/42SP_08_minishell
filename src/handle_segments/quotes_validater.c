/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_validater.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:32:29 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/25 12:43:40 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: Analyzing_quotes
 * -----------------
 * This function a pre-process to handle the quotes, it calls the function
 * even_close_quotes to check if the number of quotes is even, if it is not
 * it prints an error message and returns. If everything is ok, it calls the
 * function handle_quotes.
 *  
 * @param: *env: The hashtable that contains all the environment variables.
 * @param: **args: The array of arguments.
 * @var: *head: The head of the linked list that contains all the segments.
 * 
 * @return: Returns nothing.
 *
 */

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
