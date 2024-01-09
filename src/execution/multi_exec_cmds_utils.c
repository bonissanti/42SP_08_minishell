/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:35:32 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/09 12:21:47 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_simple(t_hashtable *hash, t_exec *exec, t_ast *node)
{
	if (analyze_cmd(hash, node) != 0)
	{
		free_for_finish(exec, hash);
		return (g_global.cmd_status);
	}
	if (is_builtin(node))
		execute_builtin(hash, node);
	else
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
	free_for_finish(exec, hash);
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

void	close_all_fds(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

t_bool	process_redirect(t_exec *exec, t_hashtable *hash, t_ast *node)
{
	exec->error_call = handle_redirects(node);
	if (exec->error_call == 1 && exec->count_pipes == 1)
	{
		g_global.cmd_status = 2;
		if (exec_multi_cmds(exec, hash, node->right) == 0)
			return (true);
	}
	g_global.cmd_status = analyze_redirect(exec, hash, node);
	return (false);
}
