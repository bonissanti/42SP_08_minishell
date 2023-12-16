/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:12:41 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/11 14:43:47 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: cmd_list_size
 * -----------------
 * The cmd_list_size function counts the amount of nodes 
 * in a t_cmd_list type struct.
 * 
 * @param: *cmd_list: The command list.
 * @var: total: The total nodes accounted from the given list.
 * @var: *head: A pointer to hold the
 * 
 * @return: int.
 * 
*/

int cmd_list_size(t_cmd_list *cmd_list)
{
	int total;
	t_cmd_list * head;

	total = 0;
	head = cmd_list;
	while(head)
	{
		head = head->next;
		total++;
	}
	return (total);
}
/**
 * Function: new_cmd_list
 * -----------------
 * The new_cmd_list function creates a new node
 * in a t_cmd_list type struct.
 * 
 * @param: node: A compound literal that is going to feed the new_node.
 * 
 * @return: t_cmd_list *.
*/

t_cmd_list	*new_cmd_list(t_cmd_list node)
{
	t_cmd_list	*new_node;

	new_node = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!new_node)
		return (NULL);
	new_node->type = node.type;
	if(node.args)
    	new_node->args = ft_strdup(node.args);
    new_node->weight = node.weight;
	if(node.infile)
    	new_node->infile = ft_strdup(node.infile);
	if(node.outfile)
    	new_node->outfile = ft_strdup(node.outfile);
   	new_node->here_doc = node.here_doc;
    new_node->next = NULL;
    new_node->prev = NULL;
	return (new_node);
}

/**
 * Function: last_cmd_list
 * -----------------
 * The last_cmd_list function returns the last node
 * of a t_cmd_list type struct.
 * 
 * @param: *cmd_list: The command list.
 * 
 * @return t_cmd_list *.
 * 
*/

t_cmd_list *last_cmd_list(t_cmd_list *cmd_list)
{
	while(cmd_list->next != NULL)
		cmd_list = cmd_list->next;
	return(cmd_list);
}

/**
 * Function: add_cmd_list
 * -----------------
 * The add_cmd_list function adds a new node
 * to the end of a t_cmd_list type struct.
 * 
 * @param: new_list: A node usually created by the new_cmd_list function.
 * 
 * @return: void.
 * 
*/

void add_cmd_list(t_cmd_list new_list)
{
	t_cmd_list *last;

	if(!cmd_list_size(g_global.cmd_list))
		g_global.cmd_list = new_cmd_list(new_list);
	else
	{
		last = last_cmd_list(g_global.cmd_list);
		last->next = new_cmd_list(new_list);
		last->next->prev = last;
	}
}

/**
 * Function: free_cmd_list
 * -----------------
 * The free_cmd_list function frees the memory
 * allocated for a t_cmd_list type struct.
 * 
 * @param: *cmd_list: The command list.
 * 
 * @return: void.
 * 
*/

void free_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_list *head;
	t_cmd_list *temp;

	head = cmd_list;
	while(head)
	{
		temp = head->next;
		ft_safe_free((void **)&head->args);
		head->here_doc_fd = 0;
		ft_safe_free((void **)&head);
		head = temp;
	}
}


// void free_cmd_list(t_cmd_list *cmd_list)
// {
// 	t_cmd_list *head;
// 	t_cmd_list *temp;
// 	char *temp_infile;
// 	char *temp_outfile;
// 	char *temp_args;

// 	head = cmd_list;
// 	while(head)
// 	{
// 		temp = head->next;
// 		temp_infile = head->infile;
// 		temp_outfile = head->outfile;
// 		temp_args = head->args;
// 		ft_safe_free((void **)&head->args);
// 		head->here_doc_fd = 0;
// 		ft_safe_free((void **)&head);
// 		temp_infile = NULL;
// 		temp_outfile = NULL;
// 		temp_args = NULL;
// 		head = temp;
// 	}
// }
