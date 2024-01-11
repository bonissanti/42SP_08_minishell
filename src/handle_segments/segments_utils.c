/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:38:47 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/09 13:08:29 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	custom_strcspn(const char *str, char *delim1)
{
	size_t	length;

	length = 0;
	while (*str)
	{
		if (*str == *delim1 || *str == '\"' || *str == '\\' || *str == ' ')
			return (length);
		str++;
		length++;
	}
	return (length);
}

char	*ft_strndup(const char *str, size_t num)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(str);
	if (num < len)
		len = num;
	dup = (char *)ft_calloc(len + 1, sizeof(char));
	if (!dup)
		return (NULL);
	while (*str && num--)
		*dup++ = *str++;
	*dup = '\0';
	return (dup - len);
}

t_bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\0')
		return (true);
	return (false);
}

void	free_expansion(t_lex *quote, t_segment *head)
{
	free_segments(head);
	free(quote->segment);
	free(quote);
}
