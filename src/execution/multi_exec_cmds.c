/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/15 13:30:16 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_bool	heredoc_first(t_exec *exec, t_shell *shell, t_ast *root)
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
		shell->cmd_status = analyze_heredoc(exec, heredoc_node, shell);
	return (true);
}

static void	handle_cmd(t_exec *exec, t_shell *shell, t_ast *root)
{
	int	initial_pipe[2];

	initial_pipe[0] = -1;
	initial_pipe[1] = -1;
	if (root->type == TYPE_COMMAND)
		exec_forked_cmd(exec, shell, root);
	if (root->type == TYPE_REDIRECT)
	{
		if (process_redirect(exec, shell, root))
			return ;
	}
	if (root->type == TYPE_PIPE)
	{
		create_files(root, exec, 0);
		handle_pipes(shell->hash, exec, root, initial_pipe);
	}
	if (root->type == TYPE_LOGICAL)
	{
		handle_logical(exec, shell, root);
		restore_fd(exec->old_stdin, exec->old_stdout, shell);
	}
}

int	exec_multi_cmds(t_exec *exec, t_ast *root, t_shell *shell)
{
	if (root == NULL)
		return (0);
	if (heredoc_first(exec, shell, root) && root->type == TYPE_PIPE)
	{
		wait_for_children(root, shell);
		close_all_fds();
		return (shell->exit_status);
	}
	handle_cmd(exec, shell, root);
	wait_for_children(root, shell);
	return (shell->exit_status);
}

int	exec_forked_cmd(t_exec *exec, t_shell *shell, t_ast *node)
{
	char	**envp;

	envp = hashtable_to_envp(shell->hash);
	if (is_builtin(node))
	{
		execute_builtin(shell, node);
		free_envp(envp);
		return (shell->exit_status);
	}
	if (analyze_cmd(shell->hash, node, shell) != 0)
	{
		free_envp(envp);
		return (shell->cmd_status);
	}
	else
		shell->cmd_status = forking(exec, shell, node, envp);
	free_envp(envp);
	return (shell->exit_status);
}

int	forking(t_exec *exec, t_shell *shell, t_ast *node, char **envp)
{
	node->pid = fork();
	exec_signals(node->pid);
	if (node->type == TYPE_COMMAND)
	{
		if (node->pid == 0)
		{
			shell->cmd_status = execve(node->path, node->args, envp);
			if (shell->cmd_status == -1)
				shell->cmd_status = 127;
			free_envp(envp);
			free_for_finish(exec, shell->hash);
			exit(shell->cmd_status);
		}
	}
	return (shell->cmd_status);
}
