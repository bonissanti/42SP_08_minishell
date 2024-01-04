/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/04 17:15:32 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		after_hdoc(t_exec *exec, t_hashtable *hash, t_ast *node,
					char *filename);
static void		open_execute(t_hashtable *hash, t_exec *exec, t_ast *node,
					char *filename);
static t_bool	verify(t_ast *node, char *line);

void	handle_heredoc(t_hashtable *hash, t_exec *exec, t_ast *node)
{
	char	*line;
	char	*filename;
	size_t	len;

	filename = generate_filename(exec->count_hdoc);
	node->out_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	signal(SIGINT, refresh_prompt);
	while (1)
	{
		len = 0;
		line = readline("> ");
		if (!verify(node, line))
			break ;
		line = check_expansion(hash, &line, &len);
		if (node->print_hdoc && line)
			ft_putendl_fd(line, node->out_fd);
		free(line);
	}
	close(node->out_fd);
	if (node->print_hdoc && !node->right)
		open_execute(hash, exec, node, filename);
	after_hdoc(exec, hash, node, filename);
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
		close_all_fds();
		free(filename);
		close(0);
		close(1);
		exit(0);
	}
	else
		free(filename);
}

static void	after_hdoc(t_exec *exec, t_hashtable *hash, t_ast *node,
		char *filename)
{
	if (node->right && node->right->type == TYPE_HEREDOC)
	{
		free(filename);
		node->left = NULL;
		exec_multi_cmds(exec, hash, node->right);
	}
	else if (node->right && (node->right->type == TYPE_REDIRECT))
		next_is_rdir(exec, hash, node, filename);
	else if (node->right && node->right->type == TYPE_PIPE)
		next_is_pipe(exec, hash, node, filename);
	if (node->right && node->right->type == TYPE_LOGICAL)
	{
		open_execute(hash, exec, node, filename);
		waitpid(node->pid, &node->num_status, 0);
		simple_logical(exec, hash, node->right, node->num_status);
	}
}

void	parent_hdoc(t_exec *exec, t_hashtable *hash, t_ast *node,
		int *next_pipe)
{
	if (exec->count_pipes >= 1)
		close(next_pipe[1]);
	if (node->right && exec->count_pipes >= 1)
		node = find_node(node, TYPE_PIPE);
	if (exec->count_pipes >= 1)
	{
		exec->count_pipes--;
		handle_pipes(hash, exec, node->right, next_pipe);
	}
	restore_fd(exec->old_stdin, exec->old_stdout);
}

static t_bool	verify(t_ast *node, char *line)
{
	if (!line || *line == '\0')
	{
		ft_fprintf(2, "minishell: warning: here-document delimited by end-of-"
			"file (wanted `%s')\n", node->delim);
		return (false);
	}
	if (!ft_strcmp(line, node->delim) || !line)
	{
		free(line);
		return (false);
	}
	return (true);
}
