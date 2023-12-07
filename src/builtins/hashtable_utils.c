/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:30:41 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 14:56:52 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"
#include "../include/builtins.h"

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
 * This is checked because if the value of the environment variable is
 * 
 * 
 * 
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
