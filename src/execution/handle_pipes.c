/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:40:02 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 17:52:17 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void	parent_pipe(int *prev_pipe, int *next_pipe)
// {
// 	if (prev_pipe && !next_pipe)
// 		close(prev_pipe[1]);
// 	if (next_pipe)
// 		close(next_pipe[1]);
// }

void	execute_pipes(t_hashtable *hashtable, t_exec *exec, t_ast *node,
		int *prev_pipe, int *next_pipe)
{
	node->pid = fork();
	exec_signals(node->pid);
	if (node->pid == 0)
	{
		if (*prev_pipe != -1)
		{
			dup2(prev_pipe[0], STDIN_FILENO);
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
		if (next_pipe && exec->count_pipes >= 1)
		{
			dup2(next_pipe[1], STDOUT_FILENO);
			close(next_pipe[0]);
			close(next_pipe[1]);
		}
		if (node->type == TYPE_REDIRECT)
		{
			handle_redirects(node);
			redirect_fds(node);
			exec_simple(hashtable, node->left);
			exit(0);
		}
		exec_simple(hashtable, node);
		exit(0);
	}
	else
	{
		wait_for_children(node);
		if (prev_pipe && !next_pipe)
			close(prev_pipe[1]);
		if (next_pipe)
			close(next_pipe[1]);
	}
}



void	handle_other(t_exec *exec, t_hashtable *hash, t_ast *node,
		int *prev_pipe)
{
	if (node->type == TYPE_LOGICAL)
	{
		execute_pipes(hash, exec, node->left, prev_pipe, NULL);
		simple_logical(exec, hash, node, node->left->num_status);
	}
	else
	{
		restore_fd(exec->old_stdin, exec->old_stdout);
		exec_multi_cmds(exec, hash, node);
	}
}


void	handle_pipes(t_hashtable *hash, t_exec *exec, t_ast *node,
		int *prev_pipe)
{
	int	next_pipe[2];

	if (node == NULL)
		return ;

	if (node->type == TYPE_PIPE)
	{
		pipe(next_pipe);
		if (node->left)
			execute_pipes(hash, exec, node->left, prev_pipe, next_pipe);
		prev_pipe[0] = next_pipe[0];
		prev_pipe[1] = next_pipe[1];
		exec->count_pipes--;
		handle_pipes(hash, exec, node->right, prev_pipe);
	}
	else if (node->right == NULL && node->type == TYPE_COMMAND)
	{
		execute_pipes(hash, exec, node, prev_pipe, NULL);
		if (prev_pipe)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
	}

	else if (node->type == TYPE_REDIRECT)
	{
		execute_pipes(hash, exec, node, prev_pipe, NULL);
		if (prev_pipe)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
	}
	else if (node->type != TYPE_PIPE && node->type != TYPE_REDIRECT)
		handle_other(exec, hash, node, prev_pipe);
}
