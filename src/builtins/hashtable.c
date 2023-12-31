/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:20:10 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/03 18:08:47 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: Create_hashtable
 * -----------------
 * This function will allocate memory for the buckets of the hashtable.
 * For default, buckets will be 101 and must be initialized to 0.
 * 
 * @var: hashtable: Pointer to the hashtable.
 * 
 * @return: Returns the pointer to the hashtable.
 *
 */

t_hashtable	*create_hashtable(void)
{
	t_hashtable	*hashtable;

	hashtable = (t_hashtable *)calloc(1, sizeof(t_hashtable));
	return (hashtable);
}

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
 * @param: *hashtable: The pointer to the hashtable.
 * @param: **envp: The environment variables.
 * 
 * @var: i: The counter for the number of environment variables.
 * @var: env: The struct that contains the key and value of the environment
 * 
 * @return: Returns nothing.
 *
 */

void	init_hash(char **envp)
{
	int		i;
	t_env	env;

	i = -1;
	g_global.hash = create_hashtable();
	g_global.hash->num_keys = 0;
	g_global.hash->home = NULL;
	while (envp[++i] != NULL)
	{
		env.equals_sign = ft_split(envp[i], '=');
		env.key = env.equals_sign[0];
		env.value = env.equals_sign[1];
		insert(g_global.hash, env.key, env.value);
		if (ft_strcmp(env.key, "HOME") == 0)
			g_global.hash->home = search(g_global.hash, env.key);
		free_split(env.equals_sign);
	}
}

/**
 * Function: Insert
 * -----------------
 * This function is used to add the environment variable to the hashtable.
 * After get index of the bucket, it will allocate memory for the new
 * environment variable and pass the key and value to the new environment.
 *  
 * @param: hashtable: The pointer to the hashtable.
 * @param: key: The environment variable name.
 * @param: value: The environment variable value.
 * 
 * @var: index: The index of the bucket.
 * @var: add_env: The new environment variable to be added.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

void	insert(t_hashtable *hashtable, char *key, char *value)
{
	size_t			index;
	t_hash			*check_dup;
	char			*key_copy;
	char			*value_copy;

	index = hash(key);
	key_copy = ft_strdup(key);
	check_dup = search(hashtable, key_copy);
	if (value != NULL)
		value_copy = ft_strdup(value);
	else
		value_copy = NULL;
	if (check_dup != NULL)
	{
		handle_value(check_dup, value, value_copy);
		safe_free((void **)&key_copy);
	}
	else
		add_new_key(hashtable, key_copy, value_copy, index);
}

/**
 * Function: Search
 * -----------------
 * This function is used to search for an environment variable in the
 * hashtable. After knowing the index of the bucket, it will iterate
 * through the hashtable until it finds the environment variable.
 * If it finds it, it will return the value of the environment variable.
 * If it does not find it, it will return NULL.
 *  
 * @param: hashtable: The pointer to the hashtable.
 * @param: key: The environment variable name.
 * 
 * @var: index: The index of the bucket.
 * @var: search_env: The environment variable to be searched.
 * 
 * @return: Returns pointer to the value of the environment variable.
 *
 */

t_hash	*search(t_hashtable *hashtable, char *key)
{
	unsigned int	index;
	t_hash			*search_env;

	index = hash(key);
	search_env = hashtable->buckets[index];
	while (search_env != NULL)
	{
		if (ft_strcmp(search_env->key, key) == 0)
			return (search_env);
		search_env = search_env->next;
	}
	return (NULL);
}

/**
 * Function: Delete
 * -----------------
 * This function is used to search for an environment variable in the
 * hashtable. After knowing the index of the bucket, it will iterate
 * through the hashtable until it finds the environment variable.
 * If it finds it, it will return the value of the environment variable.
 * If it does not find it, it will return NULL.
 *  
 * @param: hashtable: The pointer to the hashtable.
 * @param: key: The environment variable name.
 * 
 * @var: index: The index of the bucket.
 * @var: search_env: The environment variable to be searched.
 * 
 * @return: Returns pointer to the value of the environment variable.
 *
 */

void	delete_hash(t_hashtable *hashtable, char *key)
{
	unsigned int	index;
	t_hash			*delete_env;
	t_hash			*prev_env;

	index = hash(key);
	delete_env = hashtable->buckets[index];
	prev_env = NULL;
	while (delete_env != NULL)
	{
		if (ft_strcmp(delete_env->key, key) == 0)
		{
			if (prev_env == NULL)
				hashtable->buckets[index] = delete_env->next;
			else
				prev_env->next = delete_env->next;
			if (hashtable->home == delete_env)
				hashtable->home = NULL;
			safe_free_hash(delete_env);
			hashtable->num_keys--;
			return ;
		}
		prev_env = delete_env;
		delete_env = delete_env->next;
	}
}
