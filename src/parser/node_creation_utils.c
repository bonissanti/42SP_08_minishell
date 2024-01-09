/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:19:14 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/08 18:46:14 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd_list	*find_command(t_cmd_list *cmd_list)
{
	t_cmd_list	*current_command;

	current_command = NULL;
	while (cmd_list)
	{
		if (cmd_list->type == TYPE_COMMAND)
			current_command = cmd_list;
		else if (cmd_list->type == TYPE_LOGICAL || cmd_list->type == TYPE_PIPE)
			current_command = NULL;
		cmd_list = cmd_list->next;
	}
	return (current_command);
}

void	append_expand(t_tkn_list **current)
{
	while (*current && ((*current)->type == IDENTIFIER
			|| (*current)->type == EXPAND || (*current)->type == WILD))
	{
		if (!*current)
			return ;
		if ((*current)->type != IDENTIFIER && (*current)->type != EXPAND
			&& (*current)->type != WILD)
			return ;
		else
		{
			g_global.cmd_list = find_command(g_global.cmd_list);
			g_global.cmd_list->args = gnl_strjoin(g_global.cmd_list->args, " ");
			g_global.cmd_list->args = gnl_strjoin(g_global.cmd_list->args,
					(*current)->content);
		}
		g_global.cmd_list->anti_split = false;
		*current = (*current)->next;
	}
}
