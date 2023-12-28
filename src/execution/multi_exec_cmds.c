/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/28 18:05:22 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	heredoc_first(t_exec *exec, t_hashtable *hash, t_ast *root)
{
	t_bool	heredoc_executed;
	t_ast	*heredoc_node;

	heredoc_executed = false;
	if (root == NULL)
		return ;
	heredoc_node = find_node(root, TYPE_HEREDOC);
	if (root->type != TYPE_HEREDOC)
	{
		heredoc_node = find_node(root, TYPE_HEREDOC);
		if (heredoc_node && !heredoc_executed)
		{
			analyze_heredoc(exec, heredoc_node, hash);
			heredoc_executed = true;
		}
	}
}

static void	handle_cmd(t_exec *exec, t_hashtable *hash, t_ast *root)
{
	int	initial_pipe[2];

	initial_pipe[0] = -1;
	initial_pipe[1] = -1;
	if (root->type == TYPE_COMMAND)
		exec_forked_cmd(exec, hash, root);
	if (root->type == TYPE_REDIRECT)
	{
		if(handle_redirects(root) == 1)
		{
			g_global.cmd_status = 2;
			return ;
		}
		exec->error_call = handle_redirects(root);
		g_global.cmd_status = analyze_redirect(exec, hash, root);
	}
	if (root->type == TYPE_HEREDOC)
		analyze_heredoc(exec, root, hash);
	if (root->type == TYPE_PIPE)
		handle_pipes(hash, exec, root, initial_pipe);
	if (root->type == TYPE_LOGICAL)
	{
		handle_logical(exec, hash, root);
		restore_fd(exec->old_stdin, exec->old_stdout);
	}
}

int	exec_multi_cmds(t_exec *exec, t_hashtable *hashtable, t_ast *root)
{
	if (root == NULL)
		return (0);
	heredoc_first(exec, hashtable, root);
	handle_cmd(exec, hashtable, root);
	wait_for_children(root);
	return (g_global.exit_status);
}

int	exec_forked_cmd(t_exec *exec, t_hashtable *hash, t_ast *node)
{
	if (is_builtin(node))
	{
		execute_builtin(hash, node);
		return (g_global.exit_status);
	}
	if (analyze_cmd(hash, node) != 0)
		return (g_global.cmd_status);
	else
		g_global.cmd_status = forking(exec, hash, node);
	return (g_global.exit_status);
}

int	forking(t_exec *exec, t_hashtable *hash, t_ast *node)
{
	node->pid = fork();
	if (node->type == TYPE_COMMAND)
	{
		if (node->pid == 0)
		{
			if (node->path == NULL)
				g_global.cmd_status = 127;
			else
			{
				if (execve(node->path, node->args, NULL) == -1)
					g_global.cmd_status = 2;
			}
			free_for_finish(exec, hash);
			exit(g_global.cmd_status);
		}
	}
	return (g_global.cmd_status);
}
