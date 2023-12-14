/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:40:02 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/13 11:22:57 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/hash.h"

static void	parent_pipe(t_exec *exec, int *prev_pipe, int *next_pipe);
void		execute_pipes(t_hashtable *hashtable, t_vector *vtr, t_ast *node,
				int *prev_pipe, int *next_pipe);
void		pipe_from_redirect(t_hashtable *hash, t_vector *vtr, t_ast *node,
				int *prev_pipe);
static void	handle_other(t_vector *vtr, t_hashtable *hash, t_ast *node,
				int *prev_pipe);

void	handle_pipes(t_hashtable *hash, t_vector *vtr, t_ast *node,
		int *prev_pipe)
{
	int	next_pipe[2];

	if (node == NULL)
		return ;
	if (node->type == TYPE_PIPE)
	{
		pipe(next_pipe);
		execute_pipes(hash, vtr, node->left, prev_pipe, next_pipe);
		close(prev_pipe[0]);
		prev_pipe[0] = next_pipe[0];
		prev_pipe[1] = next_pipe[1];
		vtr->exec.count_pipes--;
		handle_pipes(hash, vtr, node->right, prev_pipe);
	}
	else if (node->right == NULL && node->type == TYPE_COMMAND)
	{
		execute_pipes(hash, vtr, node, prev_pipe, NULL);
		if (prev_pipe)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
	}
	else if (node->type != TYPE_PIPE)
		handle_other(vtr, hash, node, prev_pipe);
}

void	execute_pipes(t_hashtable *hashtable, t_vector *vtr, t_ast *node,
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
		if (next_pipe && vtr->exec.count_pipes >= 1)
		{
			dup2(next_pipe[1], STDOUT_FILENO);
			close(next_pipe[0]);
			close(next_pipe[1]);
		}
		execute_command(vtr, hashtable, node);
		exit(EXIT_SUCCESS);
	}
	else
		parent_pipe(&vtr->exec, prev_pipe, next_pipe);
}

static void	handle_other(t_vector *vtr, t_hashtable *hash, t_ast *node,
		int *prev_pipe)
{
	if (node->type == TYPE_REDIRECT && ft_strncmp(node->cmds, ">", 1) == 0)
	{
		handle_redirects(vtr, node);
		simple_redirect_out(vtr, hash, node, prev_pipe);
	}
	else if (node->type == TYPE_LOGICAL)
		logical_pipe(vtr, hash, node, prev_pipe);
	else
	{
		restore_fd(vtr->exec.old_stdin, vtr->exec.old_stdout);
		exec_multi_cmds(vtr, hash, node);
	}
}


static void	parent_pipe(t_exec *exec, int *prev_pipe, int *next_pipe)
{
	if (prev_pipe && !next_pipe)
		close(prev_pipe[1]);
	if (next_pipe && exec->count_pipes >= 1)
		close(next_pipe[1]);
}

void	pipe_from_redirect(t_hashtable *hash, t_vector *vtr, t_ast *node,
		int *prev_pipe)
{
	int	next_pipe[2];

	pipe(next_pipe);
	if (node == NULL)
		return ;
	if (vtr->exec.count_pipes == 0)
	{
		execute_pipes(hash, vtr, node->right, prev_pipe, NULL);
		if (prev_pipe)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
	}
	if (node->type == TYPE_PIPE && node->left)
	{
		handle_pipes(hash, vtr, node, prev_pipe);
		vtr->exec.count_pipes--;
		close(prev_pipe[0]);
	}
	else if (node->right->type == TYPE_PIPE)
		pipe_from_redirect(hash, vtr, node->right, prev_pipe);
	close(next_pipe[0]);
	close(next_pipe[1]);
}
