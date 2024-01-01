#include "../include/minishell.h"

void	handle_sigpipe(int sig)
{
	(void)sig;
	ft_putendl_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
