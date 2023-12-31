/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:38:47 by allesson          #+#    #+#             */
/*   Updated: 2024/01/02 12:57:40 by brunrodr         ###   ########.fr       */
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
