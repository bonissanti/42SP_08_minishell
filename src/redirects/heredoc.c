/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/15 11:14:57 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		after_hdoc(t_exec *exec, t_shell *shell, t_ast *node,
					char *filename);
static void		open_execute(t_hashtable *hash, t_exec *exec, t_ast *node,
					char *filename);

int	handle_heredoc(t_shell *shell, t_exec *exec, t_ast *node)
{
	char	*filename;

	filename = generate_filename(exec->count_hdoc);
	node->out_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	read_write_heredoc(shell, node);
	close(node->out_fd);
	if (shell->cmd_status == 130)
	{
		free(filename);
		return (shell->cmd_status);
	}
	exec->error_call = create_files(node, exec, 0);
	if ((exec->error_call == 1 || exec->error_call == -1)
		&& exec->count_pipes == 0)
	{
		free(filename);
		return (1);
	}
	if (node->print_hdoc && !node->right && shell->cmd_status != 130)
		open_execute(shell->hash, exec, node, filename);
	after_hdoc(exec, shell, node, filename);
	return (0);
}

static void	open_execute(t_hashtable *hash, t_exec *exec, t_ast *node,
	char *filename)
{
	node->pid = fork();
	exec_signals(node->pid);
	if (node->pid == 0)
	{
		node->in_fd = open(filename, O_RDONLY);
		dup2(node->in_fd, STDIN_FILENO);
		close(node->in_fd);
		if (node->left)
			exec_simple(hash, exec, node->left);
		else
			free_for_finish(exec, hash);
		free(filename);
		(close_all_fds(), close(0), close(1));
		exit(0);
	}
	else
		free(filename);
}

static void	after_hdoc(t_exec *exec, t_shell *shell, t_ast *node,
		char *filename)
{
	if (node->right && node->right->type == TYPE_HEREDOC)
	{
		free(filename);
		node->left = NULL;
		exec_multi_cmds(exec, node->right, shell);
	}
	else if (node->right && node->right->type == TYPE_REDIRECT)
		next_is_rdir(exec, shell->hash, node, filename);
	else if (node->right && node->right->type == TYPE_PIPE)
		next_is_pipe(exec, shell->hash, node, filename);
	if (node->right && node->right->type == TYPE_LOGICAL)
	{
		open_execute(shell->hash, exec, node, filename);
		waitpid(node->pid, &node->num_status, 0);
		simple_logical(exec, shell, node->right, node->num_status);
	}
}

void	parent_hdoc(t_exec *exec, t_hashtable *hash, t_ast *node,
		int *next_pipe)
{
	t_shell	*shell;

	shell = get_shell();
	if (exec->count_pipes >= 1)
		close(next_pipe[1]);
	if (node->right && exec->count_pipes >= 1)
		node = find_node(node, TYPE_PIPE);
	if (exec->count_pipes >= 1)
	{
		exec->count_pipes--;
		handle_pipes(hash, exec, node->right, next_pipe);
	}
	restore_fd(exec->old_stdin, exec->old_stdout, shell);
}
