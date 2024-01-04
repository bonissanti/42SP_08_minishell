/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/04 16:42:29 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

static void	heredoc_first(t_exec *exec, t_hashtable *hash, t_ast *root)
{
	t_bool	heredoc_executed;
	t_ast	*heredoc_node;

	heredoc_executed = false;
	if (root == NULL || (root && !root->left && !root->right))
		return ;
	if (root->type == TYPE_REDIRECT && root->right
		&& root->right->type == TYPE_HEREDOC)
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
	t_bool executed;

	initial_pipe[0] = -1;
	initial_pipe[1] = -1;
	executed = false;
	
	if (root->type == TYPE_COMMAND)
		exec_forked_cmd(exec, hash, root);
	if (root->type == TYPE_REDIRECT)
	{
		exec->error_call = handle_redirects(root, exec);
		if (exec->error_call == 1 && exec->count_pipes == 1)
		{
			g_global.cmd_status = 2;
			if (exec_multi_cmds(exec, hash, root->right) == 0)
				return ;
			executed = true;
		}
		if (executed)
			return ;
		g_global.cmd_status = analyze_redirect(exec, hash, root);
	}
	if (root->type == TYPE_HEREDOC)
		analyze_heredoc(exec, root, hash);
	if (root->type == TYPE_PIPE)
	{
		int ok_to_create = create_files(root, exec, 0);
		if (ok_to_create == 1 || ok_to_create == -1)
			return ;
		handle_pipes(hash, exec, root, initial_pipe);
	}
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
