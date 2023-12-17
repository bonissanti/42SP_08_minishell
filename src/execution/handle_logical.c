/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:25:55 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 17:51:52 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void	parent_logic(t_exec *exec, t_ast *node, t_hashtable *hash);

// void	logical_pipe(t_exec *exec, t_hashtable *hash, t_ast *node,
// 		int *prev_pipe)
// {
// 	if (node == NULL)
// 		return ;
// 	if (node->type == TYPE_LOGICAL)
// 	{
// 		node->pid = fork();
// 		exec_signals(node->pid);
// 		if (*prev_pipe != -1)
// 		{
// 			dup2(prev_pipe[0], STDIN_FILENO);
// 			close(prev_pipe[0]);
// 		}
// 		if (node->pid == 0)
// 		{
// 			g_global.exit_status = exec_forked_cmd(hash, node->left);
// 			exit(g_global.exit_status);
// 		}
// 		else
// 		{
// 			wait_for_children(node);
// 			parent_logic(exec, node, hash);
// 		}
// 	}
// }

// static void	parent_logic(t_exec *exec, t_ast *node, t_hashtable *hash)
// {
// 	if (node->left->num_status == 0 && !ft_strncmp(node->cmds, "&&", 2))
// 		exec_multi_cmds(exec, hash, node->right);
// 	else if (node->left->num_status != 0 && !ft_strncmp(node->cmds, "||", 2))
// 		exec_multi_cmds(exec, hash, node->right);
// }


void	simple_logical(t_exec *exec, t_hashtable *hash, t_ast *node,
		int status)
{
	if (status == 0 && !ft_strncmp(node->cmds, "&&", 2))
		exec_multi_cmds(exec, hash, node->right);
	else if (status != 0 && !ft_strncmp(node->cmds, "||", 2))
		exec_multi_cmds(exec, hash, node->right);
}