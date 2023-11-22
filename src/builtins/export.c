/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:24:59 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 12:43:01 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"
#include "../include/segments.h"
#include "../include/builtins.h"

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

void print_all_env(t_hashtable *hash_table)
{
    int i;
    char **keys;
	char *value;

    keys = copy_all_keys(hash_table);
    bubble_sort(keys, hash_table->num_keys);
    i = -1;
    while (++i < hash_table->num_keys)
	{
		value = search(hash_table, keys[i])->value;
		if (value == NULL)
			ft_printf("declare -x %s\n", keys[i]);
		else
			ft_printf("declare -x %s=\"%s\"\n", keys[i], value);
	}
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
	size_t	len;

	i = 1;
	while (args[i] != NULL)
	{
		len = 0;
		env.equals_sign = ft_split(args[i], '=');
		env.key = env.equals_sign[0];
		hash = search(hash_table, env.key);
		if (args[1][ft_strlen(args[i]) - 1] == '=')
			env_with_equals(hash_table, args, i);
		else if (env.equals_sign[1] != NULL)
			env_with_value(hash_table, args, i, len);			
		else if (hash == NULL)
			insert(hash_table, env.key, NULL);
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

void	ft_export(t_hashtable *hash_table, char **args)
{
	if (args[1] == NULL)
		print_all_env(hash_table);
	else
		add_env(hash_table, args);
}

