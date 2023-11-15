#include "../include/env.h"
#include "../include/segments.h"

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
	t_hash *current;
	char **keys;
	int index;
	int i;

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

