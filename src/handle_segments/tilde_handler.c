/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:39:58 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/10 20:55:11 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
