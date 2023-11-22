/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:39:58 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 16:48:43 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/segments.h"
#include "../include/hash.h"

void	expand_tilde(t_hashtable *hashtable, char *str)
{
	t_segment	*head;

	head = NULL;
	add_segments(&head, hashtable->home->value);
	add_segments(&head, str + 1);
	free(str);
	str = join_segments(head);
	free_segments(head);
	ft_printf("%s\n", str);
}
