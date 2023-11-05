/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:24:59 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/30 18:33:03 by brunrodr         ###   ########.fr       */
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

/**
 * Function: Init_hash
 * -----------------
 * This function is used to initialize the hashtable. It will iterate through
 * the environment variables, split them into key and value using the '='
 * character as a delimiter, and then insert them into the hashtable. This
 * function uses a counter to keep track of the number of environment variables,
 * this is used futurely to print the environment variables in alphabetical
 * order.
 *  
 * @param: *hash_table: The pointer to the hashtable.
 * @param: **envp: The environment variables.
 * 
 * @var: i: The counter for the number of environment variables.
 * @var: env: The struct that contains the key and value of the environment
 * 
 * @return: Returns nothing.
 *
 */

void init_hash(t_hashtable *hash_table, char **envp)
{
	int i;
	t_env env;

	i = -1;
	hash_table->num_keys = 0;
	while (envp[++i] != NULL)
	{
		env.equals_sign = ft_split(envp[i], '=');
		env.key = env.equals_sign[0];
		env.value = env.equals_sign[1];
		insert(hash_table, env.key, env.value);
		free_split(env.equals_sign);
	}
}

/**
 * Function: Print_all_env
 * -----------------
 * This function is used to print all the environment variables in alphabetical
 * order. First we copy all the keys into an array, then we sort the array
 * using bubble sort, and then we iterate through the array and print the
 * environment variables.
 *  
 * @param: *hash_table: The pointer to the hashtable.
 * 
 * @var: i: The counter for the number of environment variables.
 * @var: **keys: The array that contains all the keys.
 * 
 * @return: Returns nothing.
 *
 */

void	print_all_env(t_hashtable *hash_table)
{
	int		i;
	char	**keys;

	keys = copy_all_keys(hash_table);
	bubble_sort(keys, hash_table->num_keys);
	i = -1;
	while (++i < hash_table->num_keys)
		printf("declare -x %s=\"%s\"\n", keys[i], search(hash_table, keys[i])->value);
	free(keys);
}

/**
 * Function: add_env
 * -----------------
 * This function is used to add environment variables to the hashtable. First
 * we iterate through the arguments, then we split the arguments into key and
 * value using the '=' character as a delimiter. If the argument contains
 * a '=', we insert the key and value into the hashtable. If the argument
 * does not contain a '=', we search for the key in the hashtable, and if
 * 
 *  
 * @param: *hash_table: The pointer to the hashtable.
 * 
 * @var: i: The counter for the number of environment variables.
 * @var: **keys: The array that contains all the keys.
 * 
 * @return: Returns nothing.
 *
 */

void	add_env(t_hashtable *hash_table, char **args)
{
	int		i;
	t_env 	env;
	t_hash *hash;

	i = 1;
	while (args[i] != NULL)
	{
		env.equals_sign = ft_split(args[i], '=');
		env.key = env.equals_sign[0];
		hash = search(hash_table, env.key);
		if (env.equals_sign[1] != NULL)
		{
			env.value = ft_strtrim(env.equals_sign[1], "\"");
			if (env.value == NULL)
				env.value = "";
			insert(hash_table, env.key, env.value);
			free_split(env.equals_sign);
		}
		else if (hash == NULL)
		{
			env.value = "";
			insert(hash_table, env.key, env.value);	
		}
		else if (args[i][ft_strlen(args[i]) - 1] == '=')
		{
			env.value = "";
			insert(hash_table, env.key, env.value);
		}
		free_split(env.equals_sign);
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

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
	{
		safe_free((void **)&split[i]);
		i++;
	}
	safe_free((void **)&split);
}

void	ft_export(t_hashtable *hash_table, char **args)
{
	if (args[1] == NULL)
		print_all_env(hash_table);
	else
		add_env(hash_table, args);
}

