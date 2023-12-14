#include "../include/minishell.h"

int	ft_env(t_hashtable *hashtable, char **args)
{
	int		i;
	int		argc;
	char	**keys;
	char	*value;

	i = 0;
	argc = ft_count_args(args);
	keys = copy_all_keys(hashtable);
	if (argc > 1)
	{
		ft_fprintf(2, "env: %s: No such file or directory\n", args[1]);
		exit(127);
	}
	while (++i < hashtable->num_keys)
	{
		value = search(hashtable, keys[i])->value;
		if (value != NULL)
			ft_fprintf(1, "%s=%s\n", keys[i], value);
	}
	free(keys);
	return(0);
}
