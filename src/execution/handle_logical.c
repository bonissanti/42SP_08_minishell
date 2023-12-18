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

void	handle_logical(t_exec *exec, t_hashtable *hash, t_ast *node)
{
	if (node->type == TYPE_LOGICAL)
	{
		node->pid = fork();
		if (node->pid == 0)
		{
			exec_simple(hash, node->left);
			exit(0);
		}
		else
		{
			waitpid(node->pid, &node->num_status, 0);
			simple_logical(exec, hash, node, node->num_status);
		}
	}
}

void	simple_logical(t_exec *exec, t_hashtable *hash, t_ast *node,
		int status)
{
	if (status == 0 && !ft_strncmp(node->cmds, "&&", 2))
		exec_multi_cmds(exec, hash, node->right);
	else if (status != 0 && !ft_strncmp(node->cmds, "||", 2))
		exec_multi_cmds(exec, hash, node->right);
}