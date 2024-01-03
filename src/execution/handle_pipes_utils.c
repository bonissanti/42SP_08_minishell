/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:01:50 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/03 15:07:53 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	parent_pipe(int *prev_pipe, int *next_pipe)
{
	if (prev_pipe && !next_pipe)
		close(prev_pipe[1]);
	if (next_pipe)
		close(next_pipe[1]);
}

static void	redirect_pipes(t_exec *exec, int *prev_pipe, int *next_pipe)
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
		close(next_pipe[1]);
		close(next_pipe[0]);
	}
}

void	child_pipe(t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
{
	int	ok_to_create;

	redirect_pipes(exec, prev_pipe, next_pipe);
	if (node->type == TYPE_REDIRECT)
	{
		ok_to_create = create_files(node, exec);
		if (ok_to_create == 1 || ok_to_create == -1)
		{
			// close_all_fds();
			restore_fd(exec->old_stdin, exec->old_stdout);
			close (0);
			close (1);
			return ;
		}
		if (node->left)
			node = node->left;
		// else
		// 	free_for_finish(exec, g_global.hash);
		// close_all_fds();
		// close (0);
		// close (1);
		// exit(0);
	}
	if (node)
		exec_simple(g_global.hash, exec, node);
	else
		free_for_finish(exec, g_global.hash);
}

void	execute_pipes(t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
{
	node->pid = fork();
	exec_signals(node->pid);
	if (node->pid == 0)
	{
		child_pipe(exec, node, prev_pipe, next_pipe);
		close (0);
		close (1);
		exit (0);
	}
	else
		parent_pipe(prev_pipe, next_pipe);
}

t_ast	*get_last_node(t_ast *node, char *cmd)
{
	t_ast	*last_node;

	last_node = node;
	while (node != NULL)
	{
		if ((node->type == TYPE_REDIRECT && ft_strcmp(node->cmds, cmd) == 0)
			&& (!node->right || node->right->type != TYPE_REDIRECT))
			last_node = node;
		node = node->right;
	}
	return (last_node);
}
