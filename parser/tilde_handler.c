/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:55:28 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/22 18:13:11 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	expand_tilde(t_hashtable *hashtable, char **str)
{
	t_segment	*head;

	head = NULL;
	add_segments(&head, hashtable->home->value);
	add_segments(&head, *str + 1);
	// free(str);
	*str = join_segments(head);
	free_segments(head);
	ft_printf("%s\n", *str);
}