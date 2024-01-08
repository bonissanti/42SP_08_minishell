/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:54:06 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/08 14:40:08 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	redirect_to_pipe(t_exec *exec, t_ast *node, int *next_pipe,
		char *filename)
{
	node->in_fd = open(filename, O_RDONLY);
	dup2(node->in_fd, STDIN_FILENO);
	close(node->in_fd);
	if (exec->count_pipes >= 1)
	{
		dup2(next_pipe[1], STDOUT_FILENO);
		close(next_pipe[0]);
		close(next_pipe[1]);
	}
}

void	next_is_pipe(t_exec *exec, t_hashtable *hash, t_ast *node,
		char *filename)
{
	int	next_pipe[2];

	if (exec->count_pipes >= 1)
		pipe(next_pipe);
	node->pid = fork();
	exec_signals(node->pid);
	if (node->pid == 0)
	{
		redirect_to_pipe(exec, node, next_pipe, filename);
		if (node->left)
			exec_simple(hash, exec, node->left);
		else
			free_for_finish(exec, hash);
		close_all_fds();
		free(filename);
		exit(0);
	}
	else
	{
		free(filename);
		parent_hdoc(exec, hash, node, next_pipe);
	}
}

int	pipe_to_ignore(t_ast *node, int *pipe_to_ignore)
{
	t_ast	*temp;

	temp = node;
	while (temp && temp->type != TYPE_HEREDOC)
	{
		if (temp->type == TYPE_PIPE)
			(*pipe_to_ignore)++;
		temp = temp->right;
	}
	return (*pipe_to_ignore);
}

/**
 * Function: verify_eof
 * -----------------
 * This function verify_eof if the line read from the stdin is the delimiter of
 * the heredoc redirection. The first if checks if the line is empty, 
 * gerated by the ctrl+d. The second if checks if the line is the delimiter.
 * If the line is empty or the delimiter, the function returns false, and the
 * redirection is finished.
 *  
 * @param: node: The pointer to the node that contains the redirection.
 * @param: line: The line that is read from the stdin.
 * 
 * @return: Returns false if the line is empty or the delimiter, true otherwise.
 *
 */

static t_bool	verify_eof(t_ast *node, char *line)
{
	if (!line && g_global.cmd_status != 130)
	{
		ft_fprintf(2, "minishell: warning: here-document delimited by end-of-"
			"file (wanted `%s')\n", node->delim);
		return (false);
	}
	if (!ft_strcmp(line, node->delim) || g_global.cmd_status == 130)
	{
		free(line);
		return (false);
	}
	return (true);
}

void	read_write_heredoc(t_hashtable *hash, t_ast *node)
{
	char	*line;
	size_t	len;
	int		bkp_in;

	len = 0;
	signal(SIGINT, hd_quit);
	bkp_in = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (!verify_eof(node, line))
			break ;
		line = check_expansion(hash, &line, &len);
		if (node->print_hdoc && line)
			ft_putendl_fd(line, node->out_fd);
		free(line);
	}
	dup2(bkp_in, STDIN_FILENO);
}
