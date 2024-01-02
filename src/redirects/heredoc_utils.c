/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:01:00 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/02 12:58:58 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*generate_filename(int count_hdoc)
{
	char	*template;
	char	*count_str;
	char	*filename;

	template = "/tmp/heredocXXX-";
	count_str = ft_itoa(count_hdoc);
	filename = ft_strjoin(template, count_str);
	free(count_str);
	return (filename);
}

char	*check_expansion(t_hashtable *env, char **line, size_t *len)
{
	t_lex		*quote;
	t_segment	*head;
	char		*expanded;

	quote = init_lex(env, *line);
	head = NULL;
	expanded = NULL;
	if (!quote->ptr)
		return (NULL);
	while (*quote->ptr)
	{
		if (*quote->ptr == '$')
			expand_variable(quote, &head, len);
		else
		{
			quote->segment[*len] = *quote->ptr;
			(*len)++;
		}
		quote->ptr++;
	}
	quote->segment[*len] = '\0';
	add_segments(&head, quote->segment);
	expanded = join_segments(head);
	free_expansion(quote, head);
	return (expanded);
}

static void	redirect_hdoc(t_exec *exec, t_ast *node, char *filename)
{
	int	ok_to_create;

	node->in_fd = open(filename, O_RDONLY);
	dup2(node->in_fd, STDIN_FILENO);
	close(node->in_fd);
	if (node->right && node->right->type == TYPE_REDIRECT)
	{
		ok_to_create = create_files(node->right, exec);
		if (ok_to_create == 1 || ok_to_create == -1)
		{
			close_all_fds();
			restore_fd(exec->old_stdin, exec->old_stdout);
			free(filename);
			exit(0);
		}
	}
}

static void	child_rdir(t_exec *exec, t_ast *node, int *next_pipe, int index)
{
	if (index == 2 && exec->count_pipes >= 1)
	{
		dup2(next_pipe[1], STDOUT_FILENO);
		close(next_pipe[1]);
		close(next_pipe[0]);
	}
	if (node->left)
		exec_simple(g_global.hash, exec, node->left);
	else
		free_for_finish(exec, g_global.hash);
	close_all_fds();
}

void	next_is_rdir(t_exec *exec, t_hashtable *hash, t_ast *node,
		char *filename)
{
	int	next_pipe[2];
	int	index;

	index = get_index_redirect(node, TYPE_HEREDOC);
	if (exec->count_pipes >= 1)
		pipe(next_pipe);
	node->pid = fork();
	exec_signals(node->pid);
	if (node->pid == 0)
	{
		redirect_hdoc(exec, node, filename);
		child_rdir(exec, node, next_pipe, index);
		free(filename);
		exit(0);
	}
	else
	{
		free(filename);
		parent_hdoc(exec, hash, node, next_pipe);
	}
}
