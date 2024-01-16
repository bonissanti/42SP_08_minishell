/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:19:14 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/15 20:54:48 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: find_command
 * -----------------
 * This function searchs for the command that is behind
 * a delimiter operator such as |, && or ||, accordingly with
 * the cmd_list head at the given time.
 * 
 * @param: *cmd_list: The head of the command list.
 * @var: *current_command: The pointer to the command that will be returned.
 * 
 * @return: t_cmd_list *.
 * 
 */

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
/**
 * Function: append_expand
 * -----------------
 * This function appends the content of the current token
 * to a found command in the cmd_list if it is of type IDENTIFIER,
 * EXPAND or WILD.
 * 
 * @param: **current: The current token.
 * 
 * @return: void.
 * 
*/

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
