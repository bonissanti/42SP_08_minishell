/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:35:01 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/19 12:35:02 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	check_handle_error(t_lex *quote, int i)
{
	if (i == 1)
	{
		if (quote->state.single_open || quote->state.double_open)
			error_close_quotes(quote);
	}
	return (false);
}

void	error_close_quotes(t_lex *quote)
{
	ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
	free(quote->segment);
	free(quote);
	return ;
}
