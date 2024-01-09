/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:12:41 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/08 19:13:35 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmd_list_size(t_cmd_list *cmd_list)
{
	int			total;
	t_cmd_list	*head;

	total = 0;
	head = cmd_list;
	while (head)
	{
		head = head->next;
		total++;
	}
	return (total);
}

t_cmd_list	*new_cmd_list(t_cmd_list node)
{
	t_cmd_list	*new_node;

	new_node = (t_cmd_list *)ft_calloc(1, sizeof(t_cmd_list));
	if (!new_node)
		return (NULL);
	new_node->type = node.type;
	if (node.args)
		new_node->args = ft_strdup(node.args);
	else
		new_node->args = NULL;
	new_node->weight = node.weight;
	if (node.infile)
		new_node->infile = gb_to_free(ft_strdup(node.infile));
	else
		new_node->infile = NULL;
	if (node.outfile)
		new_node->outfile = gb_to_free(ft_strdup(node.outfile));
	else
		new_node->outfile = NULL;
	new_node->here_doc = node.here_doc;
	new_node->anti_split = node.anti_split;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_cmd_list	*last_cmd_list(t_cmd_list *cmd_list)
{
	while (cmd_list->next != NULL)
		cmd_list = cmd_list->next;
	return (cmd_list);
}

void	add_cmd_list(t_cmd_list new_list)
{
	t_cmd_list	*last;

	if (!cmd_list_size(g_global.cmd_list))
		g_global.cmd_list = new_cmd_list(new_list);
	else
	{
		last = last_cmd_list(g_global.cmd_list);
		last->next = new_cmd_list(new_list);
		last->next->prev = last;
	}
}

void	free_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_list	*temp;

	while (cmd_list)
	{
		temp = cmd_list->next;
		if (cmd_list->args)
			ft_safe_free((void **)&cmd_list->args);
		cmd_list->here_doc_fd = 0;
		ft_safe_free((void **)&cmd_list);
		cmd_list = temp;
	}
}
