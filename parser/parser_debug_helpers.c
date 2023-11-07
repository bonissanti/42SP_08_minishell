/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:27:30 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/06 16:14:31 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *tkn_type_string(t_tkn_type type)
{
	if(type == IDENTIFIER)
		return ("IDENTIFIER");
	else if(type == INFILE)
		return ("INFILE");
	else if(type == REDIRECT)
		return ("REDIRECT");
	else if(type == HERE_DOC)
		return ("HERE_DOC");
	else if(type == APPEND)
		return ("APPEND");
	else if(type == PIPE)
		return ("PIPE");
	else if(type == O_PARENTESIS)
		return ("O_PARENTESIS");
	else if(type == C_PARENTESIS)
		return ("C_PARENTESIS");
	else if(type == AND)
		return ("AND");
	else if(type == OR)
		return ("OR");
	else if(type == WILD)
		return ("WILD");
	else
		return ("EXPAND");
}

void print_tkn_list(t_tkn_list *tkn_list)
{
	while(tkn_list->next != NULL)
	{
		ft_printf("Token type: %s\nContent: %s\n ----------\n", 
		tkn_type_string(tkn_list->type), tkn_list->content);
		tkn_list = tkn_list->next;
	}
	ft_printf("Token type: %s\nContent: %s\n ----------\n", 
	tkn_type_string(tkn_list->type), tkn_list->content);
}