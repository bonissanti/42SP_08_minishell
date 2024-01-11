/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:17:33 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/11 12:53:25 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	child_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node,
		int *next_pipe)
{
	create_files(node, exec, 1);
	if (node->in_fd != -1 && exec->count_pipes >= 1)
	{
		dup2(next_pipe[1], STDOUT_FILENO);
		close(next_pipe[0]);
		close(next_pipe[1]);
	}
	if (exec->error_call != 1 && node->left)
		exec_simple(hashtable, exec, node->left);
	else
		free_for_finish(exec, hashtable);
	(close_all_fds(), close(1), close(0));
	exit(0);
}

static void	parent_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node,
		int *next_pipe)
{
	if (exec->count_pipes >= 1)
		close(next_pipe[1]);
	if (node->right)
		node = node->right;
	if (exec->count_pipes >= 1)
	{
		exec->count_pipes--;
		handle_pipes(hashtable, exec, node->right, next_pipe);
	}
}

void	simple_redirect(t_exec *exec, t_shell *shell, t_ast *node)
{
	int	next_pipe[2];

	if (exec->count_pipes >= 1)
		pipe(next_pipe);
	if (node->type == TYPE_REDIRECT)
	{
		node->pid = fork();
		exec_signals(node->pid);
		if (node->pid == 0)
			child_redirect(exec, shell->hash, node, next_pipe);
		else
			parent_redirect(exec, shell->hash, node, next_pipe);
	}
	if (node->right && node->right->type == TYPE_LOGICAL)
	{
		waitpid(node->pid, &node->num_status, 0);
		simple_logical(exec, shell, node->right, node->num_status);
	}
	close_all_fds();
}
