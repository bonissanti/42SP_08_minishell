/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:50:54 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/15 11:40:44 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	*ft_strtok(char *str, const char *delim)
{
	char	*input;
	char	*token;

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

char	*ft_strcat(char *dest, const char *src)
{
	char	*str;

	str = dest + ft_strlen(dest);
	while (*src)
		*str++ = *src++;
	*str = '\0';
	return ((char *)dest);
}

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*str;

	str = dest + ft_strlen(dest);
	while (*src && n--)
		*str++ = *src++;
	*str = '\0';
	return ((char *)dest);
}
