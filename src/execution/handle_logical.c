/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:25:55 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/14 14:38:43 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	parent_logic(t_vector *vtr, t_ast *node, t_hashtable *hash);

void	logical_pipe(t_vector *vtr, t_hashtable *hash, t_ast *node,
		int *prev_pipe)
{
	if (node == NULL)
		return ;
	if (node->type == TYPE_LOGICAL)
	{
		node->pid = fork();
		if (*prev_pipe != -1)
		{
			dup2(prev_pipe[0], STDIN_FILENO);
			close(prev_pipe[0]);
		}
		if (node->pid == 0)
		{
			execute_command(vtr, hash, node->left);
			exit(node->left->num_status);
		}
		else
			parent_logic(vtr, node, hash);
	}
}

static void	parent_logic(t_vector *vtr, t_ast *node, t_hashtable *hash)
{
	waitpid(node->pid, &node->left->num_status, 0);
	if (node->left->num_status == 0 && !ft_strncmp(node->cmds, "&&", 2))
		exec_multi_cmds(vtr, hash, node->right);
	else if (node->left->num_status != 0 && !ft_strncmp(node->cmds, "||", 2))
		exec_multi_cmds(vtr, hash, node->right);
}

void	simple_logical(t_vector *vtr, t_hashtable *hash, t_ast *node,
		int status)
{
	if (status == 0 && !ft_strncmp(node->cmds, "&&", 2))
		exec_multi_cmds(vtr, hash, node->right);
	else if (status != 0 && !ft_strncmp(node->cmds, "||", 2))
		exec_multi_cmds(vtr, hash, node->right);
}
