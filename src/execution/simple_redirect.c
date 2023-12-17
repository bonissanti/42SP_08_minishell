#include "../include/minishell.h"


static void	check_pipe(t_exec *exec, t_hashtable *hashtable, t_ast *node,
		int *next_pipe)
{
	if (exec->count_pipes >= 1)
	{
		exec->count_pipes--;
		close(next_pipe[1]);
		pipe_from_redirect(hashtable, exec, node->right, next_pipe);
	}
}

static void	redirect_fds(t_ast *node, int *prev_pipe)
{
	if (prev_pipe != NULL)
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

void	simple_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node)
{
	int	next_pipe[2];

	if (exec->count_pipes >= 1)
		pipe(next_pipe);
	if (node->type == TYPE_REDIRECT)
	{
		node->pid = fork();
		exec_signals(node->pid);
		redirect_fds(node, NULL);
		if (node->pid == 0)
		{
			if (node->in_fd != -1 && exec->count_pipes >= 1)
			{
				dup2(next_pipe[1], STDOUT_FILENO);
				close(next_pipe[1]);
			}
			exec_simple(hashtable, node->left);
			exit(0);
		}
		else
		{
			waitpid(node->pid, &node->left->num_status, 0);
			restore_fd(exec->old_stdin, exec->old_stdout);
			check_pipe(exec, hashtable, node, next_pipe);
		}
	}
	if (node->right && node->type == TYPE_REDIRECT && node->right->type == TYPE_LOGICAL)
	{
		waitpid(node->pid, &node->left->num_status, 0);
		simple_logical(exec, hashtable, node->right, node->left->num_status);
	}
}