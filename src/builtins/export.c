/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:24:59 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/24 19:34:23 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>
#include <string.h>

// void	init_hash(t_hashtable *hash_table, char **envp)
// {
// 	int		i;
// 	char	*key;
// 	char	*value;
// 	char	**split;

// 	i = -1;
// 	while (envp[++i] != NULL)
// 	{
// 		split = ft_split(envp[1], '=');
// 		key = split[0];
// 		value = split[1];
// 		insert(hash_table, key, value);
// 		free(split);
// 	}
// }

void init_hash(t_hashtable *hash_table, char **envp)
{
	int i;
	char *key;
	char *value;

	i = -1;
	while (envp[++i] != NULL)
	{
		key = strtok(envp[i], "=");
		value = strtok(NULL, "=");
		insert(hash_table, key, value);
	}
}

void	print_all_env(t_hashtable *hash_table)
{
	int		i;
	char	**keys;
	int		num_keys;

	keys = get_all_keys(hash_table);
	num_keys = get_num_keys(hash_table);
	bubble_sort(keys, num_keys);
	i = -1;
	while (++i < num_keys)
		printf("declare -x %s=\"%s\"\n", keys[i], search(hash_table, keys[i])->value);
	free(keys);
}

void	add_env(t_hashtable *hash_table, char **args)
{
	int		i;
	char	*key;
	char	*value;
	char	**equals_sign;
	t_hash *hash;
	// t_env *env;

	i = 1;
	while (args[i] != NULL)
	{
		equals_sign = ft_split(args[i], '=');
		if (equals_sign[1] != NULL)
		{
			key = equals_sign[0];
			value = ft_strtrim(equals_sign[1], "\"");
			if (value == NULL)
				value = "";
			insert(hash_table, key, value);
		}
		else
		{
			key = equals_sign[0];
			hash = search(hash_table, key);
			if (hash == NULL)
				value = "";
			else
				value = hash->value;
			insert(hash_table, key, value);
		}
		i++;
	}
}

/**
 * Function: Export
 * -----------------
 * This function is currently divided into two parts. At the start,
 * the function checks if there are any arguments. If there are no
 * arguments, the function prints (almost) all the environment variables.
 * If there are arguments, the function will iterate through the arguments
 * and add them to the hashtable.
 * 
 * @param: hash_table: The pointer to the hashtable.
 * @param: args: The arguments passed to the function.
 * 
 * @var: hash: The pointer to the hash node.
 * @var: name: The name of the environment variable.
 * @var: value: The value of the environment variable.
 * 
 * @return: Returns 1 if the function was successful.
 *
 */

void	ft_export(t_hashtable *hash_table, char **args)
{
	if (args[1] == NULL)
		print_all_env(hash_table);
	else
		add_env(hash_table, args);
}

