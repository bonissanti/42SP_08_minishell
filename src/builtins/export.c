/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:24:59 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/03 19:54:46 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	char	*value;

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

int	env_syntax_check(t_hashtable *hash_table, char *temp, t_env *env)
{
	if (temp && !even_close_quotes((*env).equals_sign[1]))
	{
		g_global.cmd_status = 1;
		ft_fprintf(2, "minishell: syntax error: unexpected end of file\n");
		free_split((*env).equals_sign);
		return (0);
	}
	if ((*env).equals_sign[1])
	{
		analyzing_quotes(hash_table, &temp);
		(*env).value = temp;
	}
	if (!valid_identifier_export((*env).key))
	{
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n",
			(*env).key);
		if (temp != (*env).equals_sign[1])
			free(temp);
		free((*env).equals_sign[0]);
		free((*env).equals_sign);
		g_global.cmd_status = 1;
		return (2);
	}
	return (1);
}

void	env_handler(t_env *env, char **args, int i, char *temp)
{
	t_hash	*hash;

	(void)temp;
	hash = search(g_global.hash, (*env).key);
	if (args[1][ft_strlen(args[i]) - 1] == '=')
		env_with_equals(g_global.hash, args, i);
	else if ((*env).equals_sign[1] != NULL)
		env_with_value(g_global.hash, env);
	else if (hash == NULL)
		insert(g_global.hash, (*env).key, NULL);
	if (temp != (*env).equals_sign[1])
		free(temp);
	if ((*env).value)
	{
		free((*env).value);
		(*env).value = NULL;
	}
	free((*env).equals_sign[0]);
	free((*env).equals_sign);
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
	t_env	env;
	int		syntax_status;
	char	*temp;

	env.value = NULL;
	i = 0;
	while (args[++i] != NULL)
	{
		if(ft_strlen(args[i]) == 1 && *args[i] == '=')
			env.equals_sign = ft_split(args[i], '\n');
		else
			env.equals_sign = ft_split(args[i], '=');
		env.key = env.equals_sign[0];
		temp = env.equals_sign[1];
		syntax_status = env_syntax_check(hash_table, temp, &env);
		if (!syntax_status)
			return ;
		else if (syntax_status == 2)
			continue ;
		env_handler(&env, args, i, temp);
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
	if (args[1] == NULL || *args[1] == '#')
		print_all_env(hash_table);
	else
	{
		add_env(hash_table, args);
		if(g_global.cmd_status == 1)
			return;
	}
	g_global.cmd_status = 0;
}
