/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:01:00 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/21 13:15:12 by brunrodr         ###   ########.fr       */
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
	free_segments(head);
	free(quote->segment);
	free(quote);
	return (expanded);
}

void	next_is_rdir(t_exec *exec, t_hashtable *hash, t_ast *node,
		char *filename)
{
	int ok_to_create;
	node->pid = fork();
	if (node->pid == 0)
	{
		node->in_fd = open(filename, O_RDONLY);
		dup2(node->in_fd, STDIN_FILENO);
		close(node->in_fd);
		ok_to_create = create_files(node->right);
		if (ok_to_create == 1)
			exit(0);
		exec_simple(hash, exec, node->left);
		exit(0);
	}
	else
	{
		wait(NULL);
		free(filename);
		parent_hdoc(exec, hash, node, NULL);
	}
}

void	next_is_pipe(t_exec *exec, t_hashtable *hash, t_ast *node,
		char *filename)
{
	int	next_pipe[2];

	if (exec->count_pipes >= 1)
		pipe(next_pipe);
	node->pid = fork();
	if (node->pid == 0)
	{
		node->in_fd = open(filename, O_RDONLY);
		dup2(node->in_fd, STDIN_FILENO);
		close(node->in_fd);
		if (exec->count_pipes >= 1)
		{
			dup2(next_pipe[1], STDOUT_FILENO);
			close(next_pipe[1]);
		}
		exec_simple(hash, exec, node->left);
		exit(0);
	}
	else
	{
		free(filename);
		parent_hdoc(exec, hash, node, next_pipe);
	}
}
