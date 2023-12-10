/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:11:23 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/23 17:08:05 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// size_t	ft_strcspn(const char *str, char *delim1)
// {
// 	size_t	length;

// 	length = 0;
// 	while (*str)
// 	{
// 		if (*str == *delim1)
// 			return (length);
// 		str++;
// 		length++;
// 	}
// 	return (length);
// }

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
