/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:20:18 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/12 22:09:06 by aperis-p         ###   ########.fr       */
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
	keys = ft_calloc(hash_table->num_keys, sizeof(char *));
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

void	env_with_equals(t_shell *shell, char **args, int i)
{
	char	**equals_sign;
	char	*key;
	char	*value;

	equals_sign = ft_split(args[i], '=');
	if (equals_sign[0][ft_strlen(equals_sign[0]) - 1] == '+')
		key = gb_to_free(ft_substr(equals_sign[0], 0,
					ft_strlen(equals_sign[0]) - 1), shell);
	else
		key = equals_sign[0];
	value = "";
	insert(shell->hash, key, value);
	free_split(equals_sign);
}

void	env_with_value(t_hashtable *hashtable, t_env *env)
{
	char	*key;
	char	*value;

	key = env->equals_sign[0];
	value = env->value;
	if (value == NULL)
		value = "";
	insert(hashtable, key, value);
}

int	valid_identifier_export(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (0);
	if (ft_isdigit(str[0]) || (!ft_isalpha(str[0]) && str[0] != '#')
		|| str[0] == '=')
		return (0);
	while (str[++i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+')
			return (0);
	}
	return (1);
}
