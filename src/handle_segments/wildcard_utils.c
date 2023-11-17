/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:28:30 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/17 18:47:49 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/segments.h"
#include "../include/hash.h"

t_files *create_file(char *str)
{
	t_files *file;

	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	file->content = ft_strdup(str);
	file->next = NULL;
	free(str);
	return (file);
}

void	add_new_file(t_files **head, char *str)
{
	t_files *current;
	
	if (*head == NULL)
		head = create_file(str);
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = create_file(str);
	}
}