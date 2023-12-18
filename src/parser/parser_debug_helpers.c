/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:27:30 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/11 14:43:47 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*tkn_type_string(t_tkn_type type)
{
	if (type == IDENTIFIER)
		return ("IDENTIFIER");
	else if (type == INFILE)
		return ("INFILE");
	else if (type == REDIRECT)
		return ("REDIRECT");
	else if (type == HERE_DOC)
		return ("HERE_DOC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == O_PARENTESIS)
		return ("O_PARENTESIS");
	else if (type == C_PARENTESIS)
		return ("C_PARENTESIS");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	else if (type == WILD)
		return ("WILD");
	else
		return ("EXPAND");
}

char	*cmd_type_string(t_type type)
{
	if (type == TYPE_COMMAND)
		return ("TYPE_COMMAND");
	else if (type == TYPE_LOGICAL)
		return ("TYPE_LOGICAL");
	else if (type == TYPE_PIPE)
		return ("TYPE_PIPE");
	else if (type == TYPE_FILE)
		return ("TYPE_FILE");
	else
		return ("TYPE_REDIRECT");
}
