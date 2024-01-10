/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:15:23 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/10 19:52:05 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*tkn_type_converter(t_tkn_type type)
{
	if (type == INFILE)
		return ("<");
	else if (type == REDIRECT)
		return (">");
	else if (type == HERE_DOC)
		return ("<<");
	else if (type == APPEND)
		return (">>");
	else if (type == O_PARENTESIS)
		return ("(");
	else if (type == C_PARENTESIS)
		return (")");
	else if (type == AND)
		return ("&&");
	else if (type == OR)
		return ("||");
	else
		return ("|");
}

int	set_head_tail(t_tkn_list *tokenized, t_tkn_list	**head, t_tkn_list	**tail)
{
	if (!tokenized)
	{
		get_shell()->to_exec = 2;
		return (0);
	}
	*head = tokenized;
	*tail = last_tkn_list(tokenized);
	return (1);
}
