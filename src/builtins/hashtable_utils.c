/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:30:41 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/03 18:17:48 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: Hash
 * -----------------
 * This function is used to determine the index of the bucket where the
 * key-value pair will be stored. It uses the multiplicative shift hash
 * method. Basically, based on the ASCII value of the key, it will
 * bitshift the value 5 times to the left and add the ASCII value of the
 * next character of the key. This will be done until the end of the key.
 * After that, it will use the modulo operator to get the remainder of the
 * division of the hash by the size(101) of the hashtable.
 *  
 * @param: key: The environment variable name.
 * @var: hash: The hash value, which will be the index of the bucket.
 * 
 * @return: Returns the index of the bucket.
 *
 */

unsigned int	hash(char *key)
{
	unsigned int	hash;

	hash = 0;
	while (*key)
		hash = (hash << 5) + *key++;
	return (hash % HASHSIZE);
}

/**
 * Function: handle_value
 * -----------------
 * This function is called when if from check_dup is true. It will check
 * if the value of the environment variable is different from the one
 * we are trying to insert, aka value_copy. We compare 3 cases:
 * 1. If the value of the environment variable is NULL and value_copy is not.
 * 2. If the value of the environment variable is not NULL and value_copy is.
 * 3. If the value of the environment variable and value_copy aren't NULL.
 * 
 * This is checked because if the value of the environment variable is NULL,
 * we need to free the value_copy, because we are not going to use it. If
 * the value of the environment variable is not NULL, we need to free it
 * because we are going to replace it with value_copy. If both are not NULL,
 * we need to check if they are different, because if they are, we need to
 * free the value of the environment variable and replace it with value_copy.
 *
 * @param: key: The environment variable name.
 * @var: hash: The hash value, which will be the index of the bucket.
 * 
 * @return: Returns the index of the bucket.
 *
 */

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
