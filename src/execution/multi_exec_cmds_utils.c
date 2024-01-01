/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:35:32 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/27 22:55:47 by allesson         ###   ########.fr       */
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

// temp
void fechar_todos_fds(void) {
    int max_fds = getdtablesize();
    for (int i = 3; i < max_fds; i++) {
        close(i);
    }
}

// temp
int status_do_filho(int status) 
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_fprintf(1, "\n");
			return (130);
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_fprintf(1, "QUIT\n");
			return (131);
		}
	}
	return (0);
}


int	wait_for_children(t_ast *node)
{
	int	status;
	int error;
	pid_t pid;

	status = 0;
	error = 0;
	if (node == NULL)
		return (0);
	while ((pid = waitpid(-1, &status, WUNTRACED)) > 0)
	{
		if (WIFEXITED(status))
			error = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && error == 0)
			g_global.cmd_status = WTERMSIG(status);
	}
	fechar_todos_fds();
	return (status_do_filho(status));
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
