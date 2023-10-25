#include "env.h"
#include <string.h>

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_hashtable *hash_table = create_hashtable();
	init_hash(hash_table, envp);
	char *input;

	while (1)
	{
		ft_putstr_fd("~$ \n", 1);;
		input = get_next_line(0);
		char **num_args;

		num_args = ft_split(input, ' ');
		if (strcmp(num_args[0], "export") == 0)
            ft_export(hash_table, num_args);
        
		free(input);
	}
}
