#include "../include/minishell.h"


static void	check_pipe(t_exec *exec, t_hashtable *hashtable, t_ast *node,
		int *prev_pipe)
{	

	if (exec->count_pipes >= 1)
	{
		exec->count_pipes--;
		node = node->right;
		node->pid = fork();
		if (node->pid == 0)
		{
			handle_redirects(node->right);
			dup2(node->right->out_fd, STDOUT_FILENO);
			dup2(prev_pipe[0], STDIN_FILENO);
			close(prev_pipe[0]);
			close(prev_pipe[1]);
			exec_simple(hashtable, node->right->left);
			exit(0);
		}
		else
		{
			wait_for_children(node);
			restore_fd(exec->old_stdin, exec->old_stdout);
		}
	}
}
		// handle_pipes(hashtable, exec, node->right, next_pipe);

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


			// exec_forked_cmd(hashtable, node->right->left);
			// testar com aquele TYPE_REDIRECT ADICIONAL
			exit(0);
		}
		else
		{
			wait(NULL);
			close(next_pipe[1]);
			restore_fd(exec->old_stdin, exec->old_stdout);
			int prev_pipe[2];
			prev_pipe[0] = next_pipe[0];
			prev_pipe[1] = next_pipe[1];
			check_pipe(exec, hashtable, node, prev_pipe);
		}
	}
	if (node->right && node->type == TYPE_REDIRECT && node->right->type == TYPE_LOGICAL)
	{
		waitpid(node->pid, &node->left->num_status, 0);
		simple_logical(exec, hashtable, node->right, node->left->num_status);
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