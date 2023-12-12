/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:43:27 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/11 18:34:27 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/segments.h"

static void	redirect_fds(t_ast *node, int *prev_pipe);
static void	check_pipe(t_vector *vtr, t_hashtable *hashtable, t_ast *node,
				int *next_pipe);
static void	child_redirect(t_vector *vtr, t_hashtable *hashtable, t_ast *node,
				int *next_pipe);

void	handle_redirects(t_vector *vtr, t_ast *node)
{
	t_redirect	*current;

	current = vtr->redirect;
	while (current->name)
	{
		if (ft_strcmp(current->name, node->cmds) == 0)
		{
			current->function(node, node->delim);
			break ;
		}
		current++;
	}
}

void	redirect_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node,
		int *prev_pipe)
{
	int	next_pipe[2];

	if (vtr->exec.count_pipes >= 1)
		pipe(next_pipe);
	if (node->type == TYPE_REDIRECT)
	{
		node->pid = fork();
		redirect_fds(node, prev_pipe);
		if (node->pid == 0)
		{
			child_redirect(vtr, hashtable, node, next_pipe);
		}
		else
		{
			restore_fd(vtr->exec.old_stdin, vtr->exec.old_stdout);
			if (vtr->exec.count_pipes >= 1 && node->in_fd != 0)
				close(prev_pipe[1]);
			check_pipe(vtr, hashtable, node, next_pipe);
		}
	}
	if (node->right && node->type == TYPE_REDIRECT && node->right->type == TYPE_LOGICAL)
	{
		waitpid(node->pid, &node->left->num_status, 0);
		simple_logical(vtr, hashtable, node->right, node->left->num_status);
	}
}

static void	redirect_fds(t_ast *node, int *prev_pipe)
{
	if (*prev_pipe != -1)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
	}
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

static void	child_redirect(t_vector *vtr, t_hashtable *hashtable, t_ast *node,
		int *next_pipe)
{
	if (node->type == TYPE_REDIRECT)
	{
		if (node->in_fd != -1)
		{
			dup2(next_pipe[1], STDOUT_FILENO);
			close(next_pipe[1]);
		}
		ft_fprintf(2, "husahuasuha\n");
		execute_command(vtr, hashtable, node->left);			
		exit(0);
	}
}

static void	check_pipe(t_vector *vtr, t_hashtable *hashtable, t_ast *node,
		int *next_pipe)
{
	if (vtr->exec.count_pipes >= 1)
	{
		vtr->exec.count_pipes--;
		close(next_pipe[1]);
		pipe_from_redirect(hashtable, vtr, node->right, next_pipe);
	}
}
