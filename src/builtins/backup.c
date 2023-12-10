// void	add_env(t_hashtable *hash_table, char **args)
// {
// 	int		i;
// 	t_env 	env;
// 	t_hash *hash;

// 	i = 1;
// 	while (args[i] != NULL)
// 	{
// 		env.equals_sign = ft_split(args[i], '=');
// 		env.key = env.equals_sign[0];
// 		hash = search(hash_table, env.key);
// 		if (args[1][ft_strlen(args[i]) - 1] == '=')
// 		{
// 			env.value = "";
// 			insert(hash_table, env.key, env.value);			
// 		}
// 		else if (env.equals_sign[1] != NULL)
// 		{
// 			env.value = ft_strtrim(env.equals_sign[1], "\"");
// 			if (env.value == NULL)
// 				env.value = "";
// 			insert(hash_table, env.key, env.value);
// 			free(env.value);
// 		}
// 		else if (hash == NULL)
// 			insert(hash_table, env.key, NULL);
// 		free_split(env.equals_sign);
// 		i++;
// 	}
// }
