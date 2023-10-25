#include "env.h"
#include <stdio.h>

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

int	get_num_keys(t_hashtable *hash_table)
{
	int		i;
	int		count;
	t_hash	*current;

	count = 0;
	i = -1;
	while (++i < HASHSIZE)
	{
		current = hash_table->buckets[i];
		while (current != NULL)
		{
			count++;
			current = current->next;
		}
	}
	return (count);
}

char	**get_all_keys(t_hashtable *hash_table)
{
	t_hash *current;
	int num_keys;
	char **keys;
	int index;
	int i;

	i = -1;
	index = 0;
	num_keys = get_num_keys(hash_table);
	keys = malloc(sizeof(char *) * (num_keys));
	if (keys == NULL)
		return (NULL);
	while (++i < HASHSIZE)
	{
		current = hash_table->buckets[i];
		while (current != NULL)
		{
			keys[index] = current->key;
			index++;
			current = current->next;
		}
	}
	return (keys);
}

// char **get_all_keys(t_hashtable *hash_table)
// {
//     t_hash *current;
//     char **keys;
//     int num_keys;
//     int i;

//     i = -1;
//     num_keys = get_num_keys(hash_table);
//     keys = (char **)malloc(sizeof(char *) * num_keys);
//     while (++i < HASHSIZE)
//     {
//         current = hash_table->buckets[i];
//         while (current != NULL)
//         {
//             keys[i] = current->key;
//             current = current->next;
//         }
//     }
//     return (keys);
// }
