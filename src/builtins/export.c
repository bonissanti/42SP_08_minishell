/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:24:59 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/30 18:48:28 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_' && str[0] != '=')
		return (0);
	while (str[++i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
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
	t_hash	*hash;
	size_t	len;

	i = 1;
	while (args[i] != NULL)
	{
		len = 0;
		env.equals_sign = ft_split(args[i], '=');
		env.key = env.equals_sign[0];
		char *temp = env.equals_sign[1];
		if (temp && !even_close_quotes(env.equals_sign[1]))
		{
			g_global.cmd_status = 1;
			ft_fprintf(2, "minishell: syntax error: unexpected end of file\n");
			if (temp != env.equals_sign[1])
			{
				ft_printf("passando aqui\n");
				free(temp);
			}
			free_split(env.equals_sign);
			return ;
		}
		if (env.equals_sign[1])
		{
			analyzing_quotes(hash_table, &temp);
			env.value = temp;
		}
		if (!is_valid_identifier(env.key))
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n",
				args[i]);
			if (temp != env.equals_sign[1])
			{
				ft_printf("passando aqui\n");
				free(temp);
			}
			free_split(env.equals_sign);

			g_global.cmd_status = 1;
			i++;
			continue ;
		}

		hash = search(hash_table, env.key);
		if (args[1][ft_strlen(args[i]) - 1] == '=')
			env_with_equals(hash_table, args, i);
		else if (env.equals_sign[1] != NULL)
			env_with_value(hash_table, &env, len);
		else if (hash == NULL)
			insert(hash_table, env.key, NULL);
		if (temp != env.equals_sign[1])
		{
			ft_printf("passando aqui\n");
			free(temp);
		}
		// free_split(env.equals_sign);
		free(env.equals_sign[0]);
		free(env.equals_sign);
		i++;
	}
}


// void	add_env(t_hashtable *hash_table, char **args)
// {
// 	int		i;
// 	t_env	env;
// 	t_hash	*hash;
// 	size_t	len;
// 	char *temp;

// 	i = 1;
// 	temp = NULL;
// 	while (args[i] != NULL)
// 	{
// 		len = 0;
// 		env.equals_sign = ft_split(args[i], '=');
// 		env.key = env.equals_sign[0];
// 		if (env.equals_sign[1])
// 			temp = ft_strdup(env.equals_sign[1]);

// 		if (temp && !even_close_quotes(env.equals_sign[1]))
// 		{
// 			g_global.cmd_status = 1;
// 			ft_fprintf(2, "minishell: syntax error: unexpected end of file\n");
// 			free_split(env.equals_sign);
// 			// if (temp)
// 			// 	ft_safe_free((void **)&temp);
// 			return ;
// 		}
// 		char *bkp = temp;
// 		if (env.equals_sign[1])
// 		{
// 			analyzing_quotes(hash_table, &temp);
// 			env.value = temp;
// 		}
// 		if (!is_valid_identifier(env.key))
// 		{
// 			ft_printf("minishell: export: `%s': not a valid identifier\n",
// 				args[i]);
// 			free_split(env.equals_sign);
// 			g_global.cmd_status = 1;
// 			i++;
// 			continue ;
// 		}
// 		hash = search(hash_table, env.key);
// 		if (args[1][ft_strlen(args[i]) - 1] == '=')
// 			env_with_equals(hash_table, args, i);
// 		else if (temp != NULL)
// 			env_with_value(hash_table, &env, len);
// 		else if (hash == NULL)
// 			insert(hash_table, env.key, NULL);
// 		if (bkp != temp)
// 		{
// 			ft_printf("passando aqui");
// 			ft_safe_free((void **)&temp);
// 		}
// 		free_split(env.equals_sign);
// 		// ft_safe_free((void **)&temp);
// 		i++;
// 	}
// }

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
	g_global.cmd_status = 0;
}
