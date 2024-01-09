/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:30:41 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/08 20:31:19 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

unsigned int	hash(char *key)
{
	unsigned int	hash;

	hash = 0;
	while (*key)
		hash = (hash << 5) + *key++;
	return (hash % HASHSIZE);
}

void	handle_value(t_hash *check_dup, char *value, char *value_copy)
{
	if (((check_dup->value == NULL && value != NULL))
		|| ((check_dup->value != NULL && value == NULL))
		|| ((check_dup->value != NULL && value != NULL)
			&& (ft_strcmp(check_dup->value, value) != 0)))
	{
		safe_free((void **)&check_dup->value);
		check_dup->value = value_copy;
	}
	else
		safe_free((void **)&value_copy);
}

void	add_new_key(t_hashtable *hash, char *key_copy, char *value_copy,
		size_t index)
{
	t_hash	*add_env;

	add_env = (t_hash *)ft_calloc(1, sizeof(t_hash));
	add_env->key = ft_strdup(key_copy);
	free(key_copy);
	add_env->value = value_copy;
	add_env->next = hash->buckets[index];
	hash->buckets[index] = add_env;
	hash->num_keys++;
}

void	destroy_hashtable(t_hashtable *hashtable)
{
	t_hash	*temp;
	t_hash	*next;
	size_t	i;

	i = -1;
	while (++i < HASHSIZE)
	{
		temp = hashtable->buckets[i];
		while (temp != NULL)
		{
			next = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			temp = next;
		}
	}
	free(hashtable);
}

inline	void	safe_free_hash(t_hash *delete_env)
{
	ft_safe_free((void **)&delete_env->key);
	ft_safe_free((void **)&delete_env->value);
	ft_safe_free((void **)&delete_env);
}
