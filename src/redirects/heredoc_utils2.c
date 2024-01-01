#include "../include/minishell.h"

static void	redirect_to_pipe(t_exec *exec, t_ast *node, int *next_pipe,
		char *filename)
{
	node->in_fd = open(filename, O_RDONLY);
	dup2(node->in_fd, STDIN_FILENO);
	close(node->in_fd);
	if (exec->count_pipes >= 1)
	{
		dup2(next_pipe[1], STDOUT_FILENO);
		close(next_pipe[0]);
		close(next_pipe[1]);
	}
}

void	next_is_pipe(t_exec *exec, t_hashtable *hash, t_ast *node,
		char *filename)
{
	int	next_pipe[2];

	if (exec->count_pipes >= 1)
		pipe(next_pipe);
	node->pid = fork();
	exec_signals(node->pid);
	if (node->pid == 0)
	{
		redirect_to_pipe(exec, node, next_pipe, filename);
		if (node->left)
			exec_simple(hash, exec, node->left);
		else
			free_for_finish(exec, hash);
		close_all_fds();
		free(filename);
		exit(0);
	}
	else
	{
		free(filename);
		parent_hdoc(exec, hash, node, next_pipe);
	}
}
