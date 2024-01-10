/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:19:14 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/10 17:01:27 by brunrodr         ###   ########.fr       */
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

void	append_expand(t_shell *shell, t_tkn_list **current)
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
			shell->cmd_list = find_command(shell->cmd_list);
			shell->cmd_list->args = gnl_strjoin(shell->cmd_list->args, " ");
			shell->cmd_list->args = gnl_strjoin(shell->cmd_list->args,
					(*current)->content);
		}
		shell->cmd_list->anti_split = false;
		*current = (*current)->next;
	}
}
