/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/06 17:26:25 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/hash.h"

t_bool	execute_if_builtin(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	t_cmd	*current;

	current = vtr->builtins;
	if (ft_strchr(node->cmds, '/') != NULL)
		current->cmd = ft_strrchr(node->cmds, '/') + 1;
	else
		current->cmd = node->cmds;
	while (current->name)
	{
		if (ft_strcmp(current->cmd, current->name) == 0)
		{
			current->function(hashtable, node->args + 1);
			return (true);
		}
		current++;
	}
	return (false);
}
