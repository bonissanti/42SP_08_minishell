/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:40:02 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/04 19:09:22 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_other(t_exec *exec, t_hashtable *hash, t_ast *node,
		int *prev_pipe)
{
	if (node->type == TYPE_LOGICAL)
	{
		execute_pipes(exec, node->left, prev_pipe, NULL);
		simple_logical(exec, hash, node, node->left->num_status);
	}
	else
	{
		restore_fd(exec->old_stdin, exec->old_stdout);
		exec_multi_cmds(exec, hash, node);
	}
}

static void	last_pipe(t_exec *exec, t_ast *node, int *prev_pipe)
{
	int next_pipe[2];
	if (exec->count_pipes == 0 || (exec->error_call == 1 && exec->count_pipes >= 1))
	{
		execute_pipes(exec, node, prev_pipe, NULL);
		if (prev_pipe)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
	}
	else if (exec->count_pipes >= 1)
	{
		pipe(next_pipe);
		exec->read_in = true;
		execute_pipes(exec, node, prev_pipe, next_pipe);
		prev_pipe[0] = next_pipe[0];
		prev_pipe[1] = next_pipe[1];
		// close(next_pipe[1]);
		exec->read_in = false;
		execute_pipes(exec, node->right->right, prev_pipe, NULL);
		if (prev_pipe)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
	}
}

void	handle_pipes(t_hashtable *hash, t_exec *exec, t_ast *node,
		int *prev_pipe)
{
	int	next_pipe[2];

	if (node == NULL)
		return ;
		
	if (node->right && *node->right->cmds == '>')
		exec->has_out = true;
	if (node->type == TYPE_PIPE)
	{
		pipe(next_pipe);
		if (node->left)
			execute_pipes(exec, node->left, prev_pipe, next_pipe);
		exec->has_out = false;
		prev_pipe[0] = next_pipe[0];
		prev_pipe[1] = next_pipe[1];
		if (node->right)
			handle_pipes(hash, exec, node->right, prev_pipe);
	}
	else if ((node->right == NULL && node->type != TYPE_HEREDOC)
		|| (node->type == TYPE_COMMAND || node->type == TYPE_REDIRECT))
		last_pipe(exec, node, prev_pipe);
	else if (node->type != TYPE_PIPE && node->type != TYPE_REDIRECT
		&& node->type != TYPE_HEREDOC)
		handle_other(exec, hash, node, prev_pipe);
	close_all_fds();
}
