#include "../include/hash.h"
#include "../include/segments.h"

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
	char *input;
	char *token;

	input = NULL;
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
