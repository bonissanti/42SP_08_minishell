/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tkn_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:22:03 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/16 23:22:59 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int tkn_list_size(t_tkn_list *tkn_list)
{
	int total;
	t_tkn_list * head;

	total = 0;
	head = tkn_list;
	while(head)
	{
		head = head->next;
		total++;
	}
	return (total);
}

t_tkn_list	*new_tkn_list(char *content, t_tkn_type type)
{
	t_tkn_list	*node;

	node = (t_tkn_list *)malloc(sizeof(t_tkn_list));
	if (!node)
		return (NULL);
	node->type = type;
	if(type == IDENTIFIER || type == WILD || type == EXPAND)
		node->content = content;
	else
		node->content = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_tkn_list *last_tkn_list(t_tkn_list *tkn_list)
{
	while(tkn_list->next != NULL)
		tkn_list = tkn_list->next;
	return(tkn_list);
}

void add_tkn_list(t_global *g_global, t_tkn_list *new_list)
{
	t_tkn_list *last;

	if(!tkn_list_size(g_global->tkn_list))
		g_global->tkn_list = new_list;
	else
	{
		last = last_tkn_list(g_global->tkn_list);
		last->next = new_list;
		last->next->prev = last;
	}
}

void free_tkn_list(t_tkn_list *tkn_list)
{
	t_tkn_list *head;
	t_tkn_list *temp;

	head = tkn_list;
	while(head)
	{
		temp = head->next;
		ft_safe_free((void **)&head->content);
		ft_safe_free((void **)&head);
		head = temp;
	}
}
