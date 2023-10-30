#include "env.h"
#include <string.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	// int i;
	char **num_args;
	
	// i = -1;
	(void)argc;
	(void)argv;
	(void)envp;
	t_hashtable *hash_table = create_hashtable();
	init_hash(hash_table, envp);
	char *input;
	char *trimmed_input;

	while (1)
	{
		ft_putstr_fd("~$ ", 1);;
		input = get_next_line(0);

		trimmed_input = ft_strtrim(input, "\n");
		free(input);

		num_args = ft_split(trimmed_input, ' ');
		if (ft_strcmp(num_args[0], "export") == 0)
            ft_export(hash_table, num_args);
        
		free(trimmed_input);

		if (ft_strcmp(num_args[0], "exit") == 0)
			break;

		for (int i = 0; num_args[i] != NULL; i++)
			free(num_args[i]);

		
		free(num_args);
	}
}
