/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:20:18 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/19 13:20:19 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	bubble_sort(char **array, int size)
{
	char	**first;
	char	**second;
	char	*temp;

	first = array;
	while (first < array + size)
	{
		second = first + 1;
		while (second < array + size)
		{
			if (strcmp(*first, *second) > 0)
			{
				temp = *first;
				*first = *second;
				*second = temp;
			}
			second++;
		}
		first++;
	}
}

char	**copy_all_keys(t_hashtable *hash_table)
{
	t_hash	*current;
	char	**keys;
	int		index;
	int		i;

	i = -1;
	index = 0;
	keys = malloc(sizeof(char *) * (hash_table->num_keys));
	if (keys == NULL)
		return (NULL);
	while (++i < HASHSIZE)
	{
		current = hash_table->buckets[i];
		while (current != NULL)
		{
			keys[index++] = current->key;
			current = current->next;
		}
	}
	return (keys);
}

void	env_with_equals(t_hashtable *hashtable, char **args, int i)
{
	char	**equals_sign;
	char	*key;
	char	*value;

	equals_sign = ft_split(args[i], '=');
	key = equals_sign[0];
	value = "";
	insert(hashtable, key, value);
	free_split(equals_sign);
}

void	env_with_value(t_hashtable *hashtable, t_env *env, size_t len)
{
	char		*key;
	char		*value;

	key = env->equals_sign[0];
	value = ft_strtrim(env->equals_sign[1], "\"");
	if (value == NULL)
		value = "";
	insert(hashtable, key, value);
	safe_free((void **)&value);
}
