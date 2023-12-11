/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/10 20:52:11 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
