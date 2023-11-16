/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:39:58 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/16 17:00:55 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/segments.h"
#include "../include/hash.h"

char *expand_tilde(t_hashtable *hashtable, char *str)
{
	char 	*expanded;
	size_t	len;

	if (str[0] != '~' || str[1] != '/' || str[1] != '\0')
		return (str);

	len = ft_strlen(hashtable->home->value) + ft_strlen(str);
	expanded = malloc(sizeof(char) * (len + 1));
	if (!expanded)
		return (NULL);

	ft_strlcpy(expanded, hashtable->home->value, len + 1);
	ft_strlcat(expanded, str + 1, len + 1);
	return (expanded);	
}