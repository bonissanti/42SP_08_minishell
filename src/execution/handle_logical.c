/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:25:55 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/10 17:52:00 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_logical(t_exec *exec, t_shell *shell, t_ast *node)
{
	if (node->type == TYPE_LOGICAL)
	{
		node->pid = fork();
		if (node->pid == 0)
		{
			exec_simple(shell->hash, exec, node->left);
			exit(0);
		}
		else
			simple_logical(exec, shell, node, node->num_status);
	}
}

void	simple_logical(t_exec *exec, t_shell *shell, t_ast *node, int status)
{
	wait_for_children(node, shell);
	if (status == 0 && !ft_strncmp(node->cmds, "&&", 2))
		exec_multi_cmds(exec, node->right, shell);
	else if (status != 0 && !ft_strncmp(node->cmds, "||", 2))
		exec_multi_cmds(exec, node->right, shell);
}
