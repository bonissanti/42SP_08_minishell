#include "../include/minishell.h"

// exec_forked_cmd(hashtable, node->right->left);
// testar com aquele TYPE_REDIRECT ADICIONAL

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
		else
		{
			wait(NULL);
			if (node->in_fd != -1 && exec->count_pipes >= 1)
				close(next_pipe[1]);
			restore_fd(exec->old_stdin, exec->old_stdout);
			if (node->right)
				node = node->right;
			if (node->in_fd != -1 && exec->count_pipes >= 1)
				handle_pipes(hashtable, exec, node->right, next_pipe);
		}
	}
	if (node->type == TYPE_LOGICAL)
	{
		waitpid(node->pid, &node->num_status, 0);
		simple_logical(exec, hashtable, node, node->num_status);
	}
}





void	redirect_fds(t_ast *node)
{
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