/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:25:55 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/21 13:12:48 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_logical(t_exec *exec, t_hashtable *hash, t_ast *node)
{
	if (node->type == TYPE_LOGICAL)
	{
		node->pid = fork();
		if (node->pid == 0)
		{
			exec_simple(hash, exec, node->left);
			exit(0);
		}
		else
			simple_logical(exec, hash, node, node->num_status);
	}
}

void	simple_logical(t_exec *exec, t_hashtable *hash, t_ast *node, int status)
{
	wait_for_children(node);
	if (status == 0 && !ft_strncmp(node->cmds, "&&", 2))
		exec_multi_cmds(exec, hash, node->right);
	else if (status != 0 && !ft_strncmp(node->cmds, "||", 2))
		exec_multi_cmds(exec, hash, node->right);
}
