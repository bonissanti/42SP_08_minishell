/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:35:32 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/14 14:44:00 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_simple(t_hashtable *hash, t_ast *node)
{
	if (analyze_cmd(hash, node) != 0)
		return (g_global.cmd_status);
	if (is_builtin(node))
		execute_builtin(hash, node);
	else
	{
		if (execve(node->path, node->args, NULL) == -1)
			g_global.cmd_status = 2;
		exit(g_global.cmd_status);
	}
	delete_node(g_global.ast);
	destroy_hashtable(hash);
	free_lists();
	return (g_global.exit_status);
}

void	analyze_if_print(t_ast *node, int index)
{
	t_ast	*save_node;

	save_node = node->left;
	while (node != NULL)
	{
		if (node->type == TYPE_HEREDOC && index == 0 && (node->right == NULL
				|| node->right->type != TYPE_HEREDOC))
		{
			if (node->left == NULL)
				node->left = save_node;
			node->print_hdoc = true;
		}
		if (node->type == TYPE_REDIRECT && index == 1 && (node->right == NULL
				|| node->right->type != TYPE_REDIRECT))
		{
			if (node->left == NULL)
				node->left = save_node;
			node->print_redir = true;
		}
		node = node->right;
	}
}

void	redirect_fds(t_ast *node)
{
	if (node->in_fd != -1)
	{
		dup2(node->in_fd, STDIN_FILENO);
		close(node->in_fd);
	}
	if (node->out_fd != -1)
	{
		dup2(node->out_fd, STDOUT_FILENO);
		close(node->out_fd);
	}
}

void	wait_for_children(t_ast *node)
{
	int	status;

	status = 0;
	if (node == NULL)
		return ;
	if (node->type == TYPE_REDIRECT || node->type == TYPE_COMMAND
		|| node->type == TYPE_PIPE || node->type == TYPE_HEREDOC
		|| node->type == TYPE_LOGICAL)
	{
		waitpid(node->pid, &status, 0);
		if (WIFEXITED(status) && g_global.cmd_status == 0)
			g_global.cmd_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && g_global.cmd_status == 0)
			g_global.cmd_status = WTERMSIG(status);
	}
	else if (node->right)
		wait_for_children(node->right);
}

