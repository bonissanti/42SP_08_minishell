#include "../include/minishell.h"

static void	parent_pipe(int *prev_pipe, int *next_pipe)
{
	if (prev_pipe && !next_pipe)
		close(prev_pipe[1]);
	if (next_pipe)
		close(next_pipe[1]);
}

static void	redirect_pipes(t_exec *exec, int *prev_pipe, int *next_pipe)
{
	if (*prev_pipe != -1)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (next_pipe && exec->count_pipes >= 1)
	{
		dup2(next_pipe[1], STDOUT_FILENO);
		close(next_pipe[0]);
		close(next_pipe[1]);
	}
}

void	execute_pipes(t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
{
	node->pid = fork();
	exec_signals(node->pid);
	if (node->pid == 0)
	{
		signal(SIGPIPE, SIG_IGN);
		redirect_pipes(exec, prev_pipe, next_pipe);
		if (node->type == TYPE_REDIRECT)
		{
			handle_redirects(node);
			redirect_fds(node);
			exec_simple(g_global.hash, node->left);
			exit(0);
		}
		exec_simple(g_global.hash, node);
		exit(0);
	}
	else
		parent_pipe(prev_pipe, next_pipe);
}
