/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:35:32 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/04 11:11:02 by brunrodr         ###   ########.fr       */
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
	
	if (index == 3)
		save_node = node->left;
	while (node != NULL)
	{
		if (node->type == TYPE_HEREDOC && index == 0 && (node->right == NULL
				|| node->right->type != TYPE_HEREDOC))
		{
			if (node->left == NULL && index != 3)
				node->left = save_node;
			node->print_hdoc = true;
		}
		if (node->type == TYPE_REDIRECT && (index == 1 || index == 3) && (node->right == NULL
				|| node->right->type != TYPE_REDIRECT))
		{
			if (node->left == NULL && index != 3)
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

void	ft_printf_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		ft_fprintf(2, "fd didn't have any lines to print.\n");
		return ;
	}
	while (line)
	{
		ft_fprintf(2, "es: %s", line);
		line = get_next_line(fd);
	}
	ft_fprintf(2, "____________________\n");
}
