/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/11 14:43:47 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	execute_if_builtin(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	t_cmd *current; 
	
	current = vtr->builtins;
	if (ft_strchr(node->cmds, '/') != NULL)
		current->cmd = ft_strrchr(node->cmds, '/') + 1;
	else
		current->cmd = node->cmds;
	
	while (current->name)
	{
		if (ft_strcmp(current->cmd, current->name) == 0)
		{
			ft_fprintf(2, "Executando builtin: %s\n\n", current->name);
			current->function(hashtable, node->args);
			return (true);
		}
		current++;
	}
	return (false);
}
