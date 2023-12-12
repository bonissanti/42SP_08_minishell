/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/11 11:41:54 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/segments.h"

t_ast *get_last_left(t_ast *node)
{
	t_ast *last_left = NULL;

	while (node != NULL && node->type != TYPE_COMMAND)
	{
		if (node->type == TYPE_PIPE || node->type == TYPE_REDIRECT)
			last_left = node;
		node = node->left;
	}
	return last_left;
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

void	handle_heredoc(t_vector *vtr, t_ast *node, t_hashtable *hash, char *delim)
{
	int 	next_pipe[2];
	int		fd[2];
	char	*line;
	size_t	len;

	if (delim == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token EOF\n");
		return ;
	}
	pipe(fd);
	while (1)
	{
		len = 0;
		line = readline("> ");
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		line = check_expansion(hash, &line, &len);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	if (node->left->type == TYPE_COMMAND && node->right == NULL)
		execute_command(vtr, hash, node->left);

	// if (node->left == NULL && node->right == NULL)
	// 	return ;


	// Comandos pós heredoc
	if (node->left->type == TYPE_COMMAND && node->right->type == TYPE_PIPE)
	{
		pipe(next_pipe);
		node->pid = fork();
		if (node->pid == 0)
		{
			dup2(next_pipe[1], STDOUT_FILENO);
			close(next_pipe[1]);
			execute_command(vtr, hash, node->left);
		}
		else
		{
			wait(NULL);
			close(next_pipe[1]);
			vtr->exec.count_pipes--;
			pipe_from_redirect(hash, vtr, node->right, next_pipe);
		}
	}

	else if (node->left->type == TYPE_COMMAND && node->right->type == TYPE_REDIRECT)
	{
		handle_redirects(vtr, node->right);
		dup2(node->right->out_fd, STDOUT_FILENO);
		execute_command(vtr, hash, node->left);
	}

	// outra função auxiliar
	else if (node->left->type == TYPE_COMMAND && node->right->type == TYPE_LOGICAL)
	{
		node->pid = fork();
		if (node->pid == 0)
			execute_command(vtr, hash, node->left);
		else
		{
			waitpid(node->pid, &node->left->num_status, 0);
			simple_logical(vtr, hash, node->right, node->left->num_status);
		}

	}
}
