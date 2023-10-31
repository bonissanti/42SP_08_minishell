/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:22:03 by aperis-p          #+#    #+#             */
/*   Updated: 2023/10/30 18:38:30 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tkn_list	*new_tkn_list(char *content, t_tkn_type type)
{
	t_tkn_list	*node;

	node = (t_tkn_list *)malloc(sizeof(t_tkn_list));
	if (!node)
		return (NULL);
	node->type = type;
	if(type == IDENTIFIER)
		node->content = NULL;
	else
		node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
