/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:12:41 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/20 17:04:28 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

t_cmd_list	*new_cmd_list(t_cmd_list node)
{
	t_cmd_list	*new_node;

	new_node = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!new_node)
		return (NULL);
	new_node->type = node.type;
	if(node.args)
    	new_node->args = ft_strdup(node.args);
    new_node->prec_weight = node.prec_weight;
	if(node.infile)
    	new_node->infile = ft_strdup(node.infile);
	if(node.outfile)
    	new_node->outfile = ft_strdup(node.outfile);
   	new_node->here_doc = node.here_doc;
    new_node->next = NULL;
    new_node->prev = NULL;
	return (new_node);
}

t_cmd_list *last_cmd_list(t_cmd_list *cmd_list)
{
	while(cmd_list->next != NULL)
		cmd_list = cmd_list->next;
	return(cmd_list);
}

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

void free_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_list *head;
	t_cmd_list *temp;
	char *temp_infile;
	char *temp_outfile;
	char *temp_args;

	head = cmd_list;
	while(head)
	{
		temp = head->next;
		temp_infile = head->infile;
		temp_outfile = head->outfile;
		temp_args = head->args;
		ft_safe_free((void **)&head->args);
		head->here_doc_fd = 0;
		ft_safe_free((void **)&head);
		temp_infile = NULL;
		temp_outfile = NULL;
		temp_args = NULL;
		head = temp;
	}
}
