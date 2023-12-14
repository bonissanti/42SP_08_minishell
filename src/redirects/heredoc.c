/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/14 14:54:03 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void			analyze_heredoc(t_vector *vtr, t_ast *node, t_hashtable *hashtable, char *delim);
static void		execute_heredoc(t_vector *vtr, t_ast *node, t_hashtable *hash, int *fd);
char			*check_expansion(t_hashtable *env, char **line, size_t *len);
static void 	check_next_node(t_vector *vtr, t_hashtable *hashtable, t_ast *node, int *next_pipe);

void	handle_heredoc(t_vector *vtr, t_ast *node, t_hashtable *hash, char *delim)
{
	int 	next_pipe[2] = {0};
	int		fd[2] = {0};
	char	*line = NULL;
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
		if (node->print_hdoc)
			ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	execute_heredoc(vtr, node, hash, fd);
}



void	analyze_heredoc(t_vector *vtr, t_ast *node, t_hashtable *hashtable, char *delim)
{
	analyze_if_print(node, 0);
	if (node->type == TYPE_HEREDOC)
		handle_heredoc(vtr, node, hashtable, delim);
	else
		exec_multi_cmds(vtr, hashtable, node->right);
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

static void check_next_node(t_vector *vtr, t_hashtable *hash, t_ast *node, int *next_pipe)
{
	if (node->right->type == TYPE_PIPE)
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
	else if (node->right->type == TYPE_REDIRECT)
	{
		handle_redirects(vtr, node->right);
		dup2(node->right->out_fd, STDOUT_FILENO);
		execute_command(vtr, hash, node->left);
	}
	else if (node->right->type == TYPE_LOGICAL)
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

static void	execute_heredoc(t_vector *vtr, t_ast *node, t_hashtable *hash, int *fd)
{
	if (node->print_hdoc && node->right == NULL)
	{
		node->pid = fork();
		if (node->pid == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			execute_command(vtr, hash, node->left);
		}
		else
		{
			wait(NULL);
			close(fd[0]);
		}
	}
	else if (node->right != NULL && node->right->type != TYPE_HEREDOC)
		check_next_node(vtr, hash, node, fd);
	else
	{
		restore_fd(vtr->exec.old_stdin, vtr->exec.old_stdout);
		exec_multi_cmds(vtr, hash, node->right);
	}
}
