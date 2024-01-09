/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/09 18:48:42 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_bool	heredoc_first(t_exec *exec, t_hashtable *hash, t_ast *root)
{
	int		pipes;
	t_ast	*heredoc_node;

	pipes = 0;
	if (root == NULL || (root->type != TYPE_HEREDOC && !root->left
			&& !root->right))
		return (false);
	if (root->type == TYPE_REDIRECT && root->right
		&& root->right->type == TYPE_HEREDOC && !root->left)
		return (false);
	if (exec->count_hdoc == 0)
		return (false);
	pipes = pipe_to_ignore(root, &pipes);
	exec->count_pipes -= pipes;
	heredoc_node = find_node(root, TYPE_HEREDOC);
	if (heredoc_node == NULL)
		return (false);
	else
		g_global.cmd_status = analyze_heredoc(exec, heredoc_node, hash);
	return (true);
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
		if (process_redirect(exec, hash, root))
			return ;
	}
	if (root->type == TYPE_PIPE)
	{
		create_files(root, exec, 0);
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
	if (heredoc_first(exec, hashtable, root) && root->type == TYPE_PIPE)
	{
		wait_for_children(root);
		close_all_fds();
		return (0);
	}
	handle_cmd(exec, hashtable, root);
	wait_for_children(root);
	return (g_global.exit_status);
}

int	exec_forked_cmd(t_exec *exec, t_hashtable *hash, t_ast *node)
{
	char **envp;

	envp = hashtable_to_envp(hash);
	if (is_builtin(node))
	{
		execute_builtin(hash, node);
		return (g_global.exit_status);
	}
	if (analyze_cmd(hash, node) != 0)
	{
		free(envp);	
		return (g_global.cmd_status);
	}
	g_global.cmd_status = forking(exec, hash, node, envp);
	free(envp);
	return (g_global.exit_status);
}

int	forking(t_exec *exec, t_hashtable *hash, t_ast *node, char **envp)
{
	node->pid = fork();
	if (node->type == TYPE_COMMAND)
	{
		if (node->pid == 0)
		{
			g_global.cmd_status = execve(node->path, node->args, envp);
			if (g_global.cmd_status == -1)
				g_global.cmd_status = 127;
			free(envp);
			free_for_finish(exec, hash);
			exit(g_global.cmd_status);
		}
	}
	return (g_global.cmd_status);
}
