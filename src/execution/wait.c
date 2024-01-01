#include "../include/minishell.h"

int	child_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_fprintf(1, "\n");
			return (130);
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_fprintf(1, "QUIT\n");
			return (131);
		}
	}
	return (0);
}

int	wait_for_children(t_ast *node)
{
	int		status;
	int		error;
	pid_t	pid;

	status = 0;
	error = 0;
	if (node == NULL)
		return (0);
	pid = waitpid(-1, &status, WUNTRACED);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			error = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && error == 0)
			g_global.cmd_status = WTERMSIG(status);
		pid = waitpid(-1, &status, WUNTRACED);
	}
	close_all_fds();
	return (child_status(status));
}
