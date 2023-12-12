/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tkn_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:22:03 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/11 14:43:47 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: tkn_list_size
 * -----------------
 * The tkn_list_size function counts the amount of nodes 
 * in a t_tkn_list type struct.
 * 
 * @param: *tkn_list: The command list.
 * @var: total: The total nodes accounted from the given list.
 * @var: *head: A pointer to hold the
 * 
 * @return: int.
 * 
*/

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

/**
 * Function: new_tkn_list
 * -----------------
 * The new_tkn_list function creates a new node
 * in a t_tkn_list type struct.
 * 
 * @param: node: A compound literal that is going to feed the new_node.
 * 
 * @return: t_tkn_list *.
*/

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
/**
 * Function: last_tkn_list
 * -----------------
 * The last_tkn_list function returns the last node
 * of a t_tkn_list type struct.
 * 
 * @param: *tkn_list: The command list.
 * 
 * @return t_tkn_list *.
 * 
*/

t_tkn_list *last_tkn_list(t_tkn_list *tkn_list)
{
	while(tkn_list->next != NULL)
		tkn_list = tkn_list->next;
	return(tkn_list);
}

/**
 * Function: add_tkn_list
 * -----------------
 * The add_tkn_list function adds a new node
 * to the end of a t_tkn_list type struct.
 * 
 * @param: new_list: A node usually created by the new_tkn_list function.
 * 
 * @return: void.
 * 
*/

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

/**
 * Function: free_tkn_list
 * -----------------
 * The free_tkn_list function frees the memory
 * allocated for a t_tkn_list type struct.
 * 
 * @param: *tkn_list: The command list.
 * 
 * @return: void.
 * 
*/

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
