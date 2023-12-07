/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:43:27 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:19 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/segments.h"

void	handle_redirects(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	t_redirect	*current;

	current = vtr->redirect;
	while (current->name)
	{
		if (ft_strcmp(current->name, node->cmds) == 0)
		{
			if (ft_strcmp(current->name, "<<") == 0)
				current->func_here(node, hashtable, node->delim);
			else
				current->function(node, node->delim);
			break ;
		}
		current++;
	}
}
