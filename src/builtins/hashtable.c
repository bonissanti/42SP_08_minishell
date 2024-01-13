/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:20:10 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/12 22:08:59 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_hashtable	*create_hashtable(void)
{
	t_hashtable	*hashtable;

	hashtable = (t_hashtable *)calloc(1, sizeof(t_hashtable));
	return (hashtable);
}

void	init_hash(t_shell *shell, char **envp)
{
	int		i;
	t_env	env;

	i = -1;
	shell->hash = create_hashtable();
	shell->hash->num_keys = 0;
	shell->hash->home = NULL;
	while (envp[++i] != NULL)
	{
		env.equals_sign = ft_split(envp[i], '=');
		env.key = env.equals_sign[0];
		env.value = env.equals_sign[1];
		insert(shell->hash, env.key, env.value);
		if (ft_strcmp(env.key, "HOME") == 0)
			shell->hash->home = search(shell->hash, env.key);
		free_split(env.equals_sign);
	}
}

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
