#include "../include/minishell.h"

void	double_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node)
{
	if (node->type == TYPE_REDIRECT)
	{
		node->pid = fork();
		exec_signals(node->pid);
		if (node->pid == 0)
		{
			redirect_fds(node);
			handle_redirects(node->right);
			redirect_fds(node->right);
			exec_simple(hashtable, node->right->left);
			exit(0);
		}
		else
		{
			wait(NULL);
			node->left = NULL;
			restore_fd(exec->old_stdin, exec->old_stdout);
			exec_multi_cmds(exec, hashtable, node->right->right);
		}
	}
}

static void	child_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node,
		int *next_pipe)
{
	redirect_fds(node);
	if (node->in_fd != -1 && exec->count_pipes >= 1)
	{
		dup2(next_pipe[1], STDOUT_FILENO);
		close(next_pipe[1]);
	}
	exec_simple(hashtable, node->left);
	exit(0);
}

static void	parent_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node,
		int *next_pipe)
{
	if (exec->count_pipes >= 1)
		close(next_pipe[1]);
	restore_fd(exec->old_stdin, exec->old_stdout);
	if (node->right)
		node = node->right;
	if (exec->count_pipes >= 1)
		handle_pipes(hashtable, exec, node->right, next_pipe);
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
		if (node->pid == 0)
			child_redirect(exec, hashtable, node, next_pipe);
		else
			parent_redirect(exec, hashtable, node, next_pipe);
	}
	if (node->type == TYPE_LOGICAL)
	{
		waitpid(node->pid, &node->num_status, 0);
		simple_logical(exec, hashtable, node, node->num_status);
	}
}
