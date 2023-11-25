/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/24 19:07:06 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/builtins.h"
#include "../include/hash.h"

void	init_builtins(t_vector *vtr)
{
	vtr->builtins[0].cmd = NULL;
	vtr->builtins[0].name = "echo";
	vtr->builtins[0].function = ft_echo;
	vtr->builtins[1].name = NULL;
	vtr->builtins[1].function = NULL;
}

t_bool	is_builtins(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	if (ft_strchr(node->cmds, '/') != NULL)
		vtr->builtins->cmd = ft_strrchr(node->cmds, '/') + 1;
	else
		vtr->builtins->cmd = node->cmds;
	
	while (vtr->builtins->name)
	{
		if (ft_strcmp(vtr->builtins->cmd, vtr->builtins->name) == 0)
		{
			execute_builtins(vtr->builtins, hashtable, node);
			return (true);
		}
		vtr->builtins++;
	}
	return (false);
}

void	execute_builtins(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	while (vtr->builtins->name)
	{
		if (ft_strcmp(vtr->builtins->cmd, vtr->builtins->name) == 0)
		{
			vtr->builtins->function(hashtable, node->args);
			break ;
		}
		vtr->builtins++;
	}
}
