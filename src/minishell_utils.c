#include "./include/builtins.h"
#include "./include/hash.h"

void init_structs(void *structs, int type, size_t struct_size)
{
	ft_memset(structs, type, struct_size);
}

int	ft_count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
	{
		if(split[i] != NULL)
		{
			free(split[i]);
			split[i] = NULL;
		}
		i++;
	}
	if(split != NULL)
	{
		free(split);
		split = NULL;
	}
}

void	safe_free(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
