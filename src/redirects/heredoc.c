/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 17:56:06 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char			*check_expansion(t_hashtable *env, char **line, size_t *len);
static void 	open_execute(t_hashtable *hash, t_ast *node, char *filename);
// static void 	check_next_node(t_exec *exec, t_hashtable *hashtable, t_ast *node);
static char 	*generate_filename(int count_hdoc);

static char *generate_filename(int count_hdoc)
{
	char *template;
	char *count_str;
	char *filename;
	
	template = "/tmp/heredocXXX-";
	count_str = ft_itoa(count_hdoc);
	filename = ft_strjoin(template, count_str);

	free(count_str);
	return (filename);
}

void handle_heredoc(t_hashtable *hash, t_exec *exec, t_ast *node)
{
	char *line;
	char *filename;

	filename = generate_filename(exec->count_hdoc);
	node->out_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, node->delim))
		{
			free(line);
			break ;
		}
		if (node->print_hdoc)
			ft_putendl_fd(line, node->out_fd);
		free(line);
	}
	close(node->out_fd);
	if (node->print_hdoc)
		open_execute(hash, node, filename);
}

static void open_execute(t_hashtable *hash, t_ast *node, char *filename)
{
	
	analyze_cmd(hash, node->left);
	node->pid = fork();
	if (node->pid == 0)
	{
		node->in_fd = open(filename, O_RDONLY);
		dup2(node->in_fd, STDIN_FILENO);
		close(node->in_fd);
		execve(node->left->path, node->left->args, NULL);
		exit(0);
	}
	else
		wait(NULL);
}

void	analyze_heredoc(t_exec *exec, t_ast *node, t_hashtable *hashtable)
{
	analyze_if_print(node, 0);
	if (node->type == TYPE_HEREDOC)
		handle_heredoc(hashtable, exec, node);
	else
		exec_multi_cmds(exec, hashtable, node->right);
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

// static void check_next_node(t_exec *exec, t_hashtable *hash, t_ast *node)
// {
// 	int next_pipe[2];
	
// 	if (node->right->type == TYPE_PIPE)
// 	{
// 		pipe(next_pipe);
// 		node->pid = fork();
// 		if (node->pid == 0)
// 		{
// 			dup2(next_pipe[1], STDOUT_FILENO);
// 			close(next_pipe[1]);
// 			execute_command(hash, node->left);
// 		}
// 		else
// 		{
// 			wait(NULL);
// 			close(next_pipe[1]);
// 			exec->count_pipes--;
// 			pipe_from_redirect(hash, exec, node->right, next_pipe);
// 		}
// 	}
// 	else if (node->right->type == TYPE_REDIRECT)
// 	{
// 		handle_redirects(node->right);
// 		dup2(node->right->out_fd, STDOUT_FILENO);
// 		execute_command(hash, node->left);
// 	}
// 	else if (node->right->type == TYPE_LOGICAL)
// 	{
// 		node->pid = fork();
// 		if (node->pid == 0)
// 			execute_command(hash, node->left);
// 		else
// 		{
// 			waitpid(node->pid, &node->left->num_status, 0);
// 			simple_logical(exec, hash, node->right, node->left->num_status);
// 		}
// 	}
// }
