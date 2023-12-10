/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:47:48 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 18:47:57 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/segments.h"

static int	is_delimiter(char c, char delimiter, t_bool in_quotes)
{
	if (c == delimiter && !in_quotes)
		return (1);
	return (0);
}

static size_t	ft_del_count(char const *s, char c)
{
	size_t		counter;
	char const	*ptr;
	int			i;
	t_bool		in_quotes;

	ptr = s;
	counter = 0;
	i = 0;
	in_quotes = 0;
	while (*(ptr + i))
	{
		while (is_delimiter(*(ptr + i), c, in_quotes) && *(ptr + i) != '\0')
			i++;
		while (!is_delimiter(*(ptr + i), c, in_quotes) && *(ptr + i) != '\0')
		{
			if (*(ptr + i) == '\"' || *(ptr + i) == '\'')
				in_quotes = !in_quotes;
			i++;
		}
		if (*(ptr + i) != '\0' || !is_delimiter(*(ptr + i - 1), c, in_quotes))
			counter++;
	}
	return (counter);
}

static	int	ft_btw(char const *s, char c)
{
	int			counter;
	char const	*ptr;
	int			i;
	t_bool		in_quotes;

	ptr = s;
	if (is_delimiter(*(ptr + 0), c, false))
		i = 1;
	else
		i = 0;
	counter = 0;
	in_quotes = false;
	while (*(ptr + i))
	{
		if (is_delimiter(*(ptr + i), c, in_quotes))
		{
			return (counter);
		}
		if (*(ptr + i) == '\"' || *(ptr + i) == '\'')
			in_quotes = !in_quotes;
		counter ++;
		i++;
	}
	return (counter);
}

char	**ast_split(char const *s, char c)
{
	char		**result;
	char		**temp;

	result = (char **) malloc((ft_del_count(s, c) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	temp = result;
	while (*s)
	{
		if (!is_delimiter(*s, c, false))
		{
			*temp = malloc((ft_btw(s, c) + 1) * sizeof(char));
			if (*temp == NULL)
				return (NULL);
			ft_strlcpy(*temp++, s, ft_btw(s, c) + 1);
			s += ft_btw(s, c);
		}
		else
			s++;
	}
	*temp = NULL;
	return (result);
}
