#include "../include/builtins.h"
#include "../include/hash.h"

void	free_for_exit(t_hashtable *hash_table, char **args, int argc);

void	ft_exit(t_hashtable *hash_table, char **args)
{
	long int	exit_code;
	int			argc;

	exit_code = 0;
	argc = ft_count_args(args);
	if (argc == 1)
	{
		destroy_hashtable(hash_table);
		free_split(args);
		exit(0);
	}
	else if (argc == 2)
	{
		if (!ft_isdigit(args[1][0]))
			ft_fprintf(2, "exit: %s: numeric argument required\n", args[1]);
		exit_code = ft_atol(args[1]);
		destroy_hashtable(hash_table);
		free_split(args);
		exit(exit_code);
	}
	else
		ft_putstr_fd("exit: too many arguments\n", 2);
}
