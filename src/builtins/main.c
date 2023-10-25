#include "env.h"
#include <string.h>

int	main(int argc, char **argv, char **envp)
{
	int i;
	char **num_args;
	
	i = -1;
	(void)argc;
	(void)argv;
	(void)envp;
	t_hashtable *hash_table = create_hashtable();
	init_hash(hash_table, envp);
	char *input;

	while (1)
	{
		ft_putstr_fd("~$ ", 1);;
		input = get_next_line(0);

		num_args = ft_split(input, ' ');
		if (ft_strcmp(num_args[0], "export\n") == 0)
            ft_export(hash_table, num_args);
        
		free(input);

		while (num_args[++i] != NULL)
			free(num_args[i]);
		free(num_args);
	}
}
