/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:40:02 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/14 18:20:12 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	parent_pipe(t_exec *exec, int *prev_pipe, int *next_pipe);
void		execute_pipes(t_hashtable *hashtable, t_exec *exec, t_ast *node,
				int *prev_pipe, int *next_pipe);
void		pipe_from_redirect(t_hashtable *hash, t_exec *exec, t_ast *node,
				int *prev_pipe);
static void	handle_other(t_exec *exec, t_hashtable *hash, t_ast *node,
		int *prev_pipe);
		
void	handle_pipes(t_hashtable *hash, t_exec *exec, t_ast *node,
		int *prev_pipe)
{
	int	next_pipe[2];

	if (node == NULL)
		return ;
	if (node->type == TYPE_PIPE)
	{
		pipe(next_pipe);
		execute_pipes(hash, exec, node->left, prev_pipe, next_pipe);
		close(prev_pipe[0]);
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
	else if (node->type != TYPE_PIPE)
		handle_other(exec, hash, node, prev_pipe);
}

void	execute_pipes(t_hashtable *hashtable, t_exec *exec, t_ast *node,
		int *prev_pipe, int *next_pipe)
{
	node->pid = fork();
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
		g_global.exit_status = execute_command(hashtable, node);
		exit(EXIT_SUCCESS);
	}
	else
		parent_pipe(exec, prev_pipe, next_pipe);
}

static void	parent_pipe(t_exec *exec, int *prev_pipe, int *next_pipe)
{
	if (prev_pipe && !next_pipe)
		close(prev_pipe[1]);
	if (next_pipe && exec->count_pipes >= 1)
		close(next_pipe[1]);
}

static void	handle_other(t_exec *exec, t_hashtable *hash, t_ast *node,
		int *prev_pipe)
{
	if (node->type == TYPE_REDIRECT && ft_strncmp(node->cmds, ">", 1) == 0)
	{
		handle_redirects(node);
		simple_redirect_out(exec, hash, node, prev_pipe);
	}
	else if (node->type == TYPE_LOGICAL)
		logical_pipe(exec, hash, node, prev_pipe);
	else
	{
		restore_fd(exec->old_stdin, exec->old_stdout);
		exec_multi_cmds(exec, hash, node);
	}
}


void	pipe_from_redirect(t_hashtable *hash, t_exec *exec, t_ast *node,
		int *prev_pipe)
{
	int	next_pipe[2];

	pipe(next_pipe);
	if (node == NULL)
		return ;
	if (exec->count_pipes == 0)
	{
		execute_pipes(hash, exec, node->right, prev_pipe, NULL);
		if (prev_pipe)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
	}
	if (node->type == TYPE_PIPE && node->left)
	{
		handle_pipes(hash, exec, node, prev_pipe);
		exec->count_pipes--;
		close(prev_pipe[0]);
	}
	else if (node->right->type == TYPE_PIPE)
		pipe_from_redirect(hash, exec, node->right, prev_pipe);
	close(next_pipe[0]);
	close(next_pipe[1]);
}

