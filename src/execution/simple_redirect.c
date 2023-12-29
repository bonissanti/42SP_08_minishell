/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:17:33 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/27 22:55:01 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	double_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node)
{
	if (node->type == TYPE_REDIRECT)
	{
		node->pid = fork();
		exec_signals(node->pid);
		if (node->pid == 0)
		{
			redirect_fds(node);
			handle_redirects(node->right);
			redirect_fds(node->right);
			if (exec->error_call != 1 && node->left)
				exec_simple(hashtable, exec, node->right->left);
			delete_node(g_global.ast);
			destroy_hashtable(hashtable);
			free_lists();
			empty_trash_can();
			restore_fd(exec->old_stdin, exec->old_stdout);
			exit(0);
		}
		else
		{
			wait(NULL);
			close(node->in_fd);
			node->left = NULL;
			restore_fd(exec->old_stdin, exec->old_stdout);
			exec_multi_cmds(exec, hashtable, node->right->right);
		}
	}
}

static void	child_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node,
		int *next_pipe)
{
	redirect_fds(node);
	if (node->in_fd != -1 && exec->count_pipes >= 1)
	{
		dup2(next_pipe[1], STDOUT_FILENO);
		close(next_pipe[0]);
		close(next_pipe[1]);
	}
	if (exec->error_call != 1 && node->left)
		exec_simple(hashtable, exec, node->left);
	close(node->in_fd);
	delete_node(g_global.ast);
	destroy_hashtable(hashtable);
	free_lists();
	empty_trash_can();
	restore_fd(exec->old_stdin, exec->old_stdout);
	fechar_todos_fds();
	exit(0);
}

static void	parent_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node,
		int *next_pipe)
{
	if (exec->count_pipes >= 1)
		close(next_pipe[1]);
	close(node->in_fd);
	restore_fd(exec->old_stdin, exec->old_stdout);
	if (node->right)
		node = node->right;
	if (exec->count_pipes >= 1)
		handle_pipes(hashtable, exec, node->right, next_pipe);
}

void	redirect_in(t_exec *exec, t_hashtable *hashtable, t_ast *node)
{
	int	next_pipe[2];

	if (exec->count_pipes >= 1)
		pipe(next_pipe);
	if (node->type == TYPE_REDIRECT)
	{
		node->pid = fork();
		exec_signals(node->pid);
		if (node->pid == 0)
			child_redirect(exec, hashtable, node, next_pipe);
		else
			parent_redirect(exec, hashtable, node, next_pipe);
	}
	if (node->right && node->right->type == TYPE_LOGICAL)
	{
		waitpid(node->pid, &node->num_status, 0);
		simple_logical(exec, hashtable, node->right, node->num_status);
	}
	close(node->in_fd);
	fechar_todos_fds();
}

void	redirect_out(t_exec *exec, t_hashtable *hash, t_ast *node)
{
	if (node == NULL)
		return ;
	node->pid = fork();
	if (node->pid == 0)
	{
		handle_redirects(node);
		redirect_fds(node);
		if (node->left)
			exec_simple(hash, exec, node->left);
		close(node->out_fd);
		delete_node(g_global.ast);
		destroy_hashtable(hash);
		free_lists();
		empty_trash_can();
		restore_fd(exec->old_stdin, exec->old_stdout);
		fechar_todos_fds();
		exit(0);
	}
	else
	{
		close(node->out_fd);
		if (node->num_status == 0)
			exec_multi_cmds(exec, hash, node->right);
	}
}
