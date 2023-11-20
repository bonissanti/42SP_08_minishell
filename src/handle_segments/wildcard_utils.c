#include "../include/hash.h"
#include "../include/temp.h"
#include "../include/segments.h"

void init_structs(void *structs, size_t struct_size)
{
	memset(structs, 0, sizeof(struct_size));
}

size_t	ft_strcspn(const char *str, char *delim1)
{
	size_t	length;

	length = 0;
	while (*str)
	{
		if (*str == *delim1)
			return (length);
		str++;
		length++;
	}
	return (length);
}

char *ft_strtok(char *str, const char *delim)
{
	static char *input;
	char *token;

	if (str)
		input = str;
	if (!input)
		return (NULL);
	token = input;
	while (*input)
	{
		if (ft_strchr(delim, *input))
		{
			*input++ = '\0';
			return (token);
		}
		input++;
	}
	if (*token == '\0')
		return (NULL);
	return (token);
}