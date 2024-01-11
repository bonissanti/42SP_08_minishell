/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:01:50 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/11 13:53:29 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	parent_pipe(t_exec *exec, int *prev_pipe, int *next_pipe)
{
	if (prev_pipe && !next_pipe)
		close(prev_pipe[1]);
	if (next_pipe)
		close(next_pipe[1]);
	exec->count_pipes--;
}

static void	redirect_pipes(t_exec *exec, int *prev_pipe, int *next_pipe)
{
	if (*prev_pipe != -1 && !exec->read_in)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (next_pipe && exec->count_pipes >= 1)
	{
		dup2(next_pipe[1], STDOUT_FILENO);
		close(next_pipe[1]);
		close(next_pipe[0]);
	}
}

void	child_pipe(t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
{
	t_shell	*shell;

	shell = get_shell();
	if (node->type == TYPE_PIPE || node->type == TYPE_COMMAND || exec->has_out
		|| exec->read_in)
		redirect_pipes(exec, prev_pipe, next_pipe);
	else
		close(next_pipe[0]);
	if (node->type == TYPE_REDIRECT && node->to_exec)
	{
		create_files(node, exec, 1);
		if (node->left && node->to_exec)
			node = node->left;
		else
			free_for_finish(exec, shell->hash);
	}
	if (node && node->to_exec)
		exec_simple(shell->hash, exec, node);
	else
		free_for_finish(exec, shell->hash);
	(close_all_fds(), close(0), close(1));
	exit(0);
}

void	execute_pipes(t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
{
	node->pid = fork();
	exec_signals(node->pid);
	if (node->pid == 0)
		child_pipe(exec, node, prev_pipe, next_pipe);
	else
		parent_pipe(exec, prev_pipe, next_pipe);
}
