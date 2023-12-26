#include "../include/minishell.h"

int	ft_exit(char **args)
{
	int	argc;

	g_global.exit_status = 0;
	argc = ft_count_args(args);
	if (argc > 2)
	{
		ft_fprintf(2, "exit: too many arguments\n");
		if (!ft_isdigit(args[1][0]))
			g_global.exit_status = 2;
		else
			g_global.exit_status = 1;
	}
	else if (argc == 2)
	{
		if (!ft_isdigit(args[1][0]) && args[1][0] != '-' && args[1][0] != '+')
		{
			ft_fprintf(2, "exit: %s: numeric argument required\n", args[1]);
			g_global.exit_status = 2;
		}
		if (ft_isdigit(args[1][0]) || args[1][0] == '-' || args[1][0] == '+')
			g_global.exit_status = ft_atoi(args[1]) % 256;
	}
	g_global.cmd_status = g_global.exit_status;
	return (g_global.exit_status);
}
