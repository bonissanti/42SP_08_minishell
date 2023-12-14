#include "../include/minishell.h"

void	free_for_exit(t_hashtable *hash_table, char **args, int argc);

void	ft_exit(t_hashtable *hash_table, char **args)
{
	long int	exit_code;
	int			argc;

	exit_code = 0;
	argc = ft_count_args(args);
	if (argc > 2)
	{
		ft_fprintf(2, "exit: too many arguments\n");
		g_global.exit_status = 2;
	}
	
	else if (argc == 2)
	{
		if (!ft_isdigit(args[1][0]) && args[1][0] != '-')
		{
			ft_fprintf(2, "exit: %s: numeric argument required\n", args[1]);
			g_global.exit_status = 2;
		}
		if (ft_isdigit(args[1][0]))
			g_global.exit_status = ft_atoi(args[1]);
	}
	// destroy_hashtable(hash_table);
	kill(0, SIGINT);
}
