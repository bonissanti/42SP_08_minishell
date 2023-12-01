/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/29 18:15:52 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/builtins.h"
#include "../include/hash.h"

void	init_cmd(t_vector *vtr)
{
	vtr->builtins[0].cmd = NULL;
	vtr->builtins[0].name = "echo";
	vtr->builtins[0].function = ft_echo;
	vtr->builtins[1].name = NULL;
	vtr->builtins[1].function = NULL;
}

t_bool	execute_if_builtin(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	t_cmd *current; 
	
	if(!node)
		return (false);
	current = vtr->builtins;
	if (ft_strchr(node->cmds, '/') != NULL)
		current->cmd = ft_strrchr(node->cmds, '/') + 1;
	else
		current->cmd = node->cmds;
	
	while (current->name)
	{
		if (ft_strcmp(current->cmd, current->name) == 0)
		{
			current->function(hashtable, node->args);
			return (true);
		}
		current++;
	}
	return (false);
}
