#include "env.h"
#include <string.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	char **num_args;
	
	(void)argc;
	(void)argv;
	(void)envp;
	t_hashtable *hash_table = create_hashtable();
	init_hash(hash_table, envp);
	char *input;
	char *trimmed_input;

	while (1)
	{
		ft_putstr_fd("~$ ", 1);
		input = get_next_line(0);

		trimmed_input = ft_strtrim(input, "\n");
		free(input);

		num_args = ft_split(trimmed_input, ' ');
		free(trimmed_input);
		
		if (ft_strcmp(num_args[0], "export") == 0)
           ft_export(hash_table, num_args);

		if (ft_strcmp(num_args[0], "echo") == 0)
			ft_echo(hash_table, num_args);
       
		if (ft_strcmp(num_args[0], "exit") == 0)
			ft_exit(num_args);

		if (ft_strcmp(num_args[0], "unset") == 0)
			ft_unset(hash_table, num_args);

		for (int i = 0; num_args[i] != NULL; i++)
			free(num_args[i]);
		free(num_args);
		
	}

	destroy_hashtable(hash_table);
	free(hash_table);
	// for (int i = 0; envp[i] != NULL; i++)
	// 	delete_hash(hash_table, envp[i]);
	return (0);
}
