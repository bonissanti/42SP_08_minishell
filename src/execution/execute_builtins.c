/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/24 17:15:19 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"
#include "../include/hash.h"

void	init_builtins(t_cmd *cmd)
{
	cmd[0].name = "echo";
	cmd[0].function = ft_echo;
}

// cmd[1].name = "export";
	// cmd[1].function = ft_export;
	// cmd[2].name = "cd";
	// cmd[2].function = ft_cd;
	// cmd[3].name = "unset";
	// cmd[3].function = ft_unset;
	// cmd[4].name = "env";
	// cmd[4].function = ft_env;
	// cmd[5].name = "exit";
	// cmd[5].function = ft_exit;
	// cmd[6].name = "pwd";
	// cmd[6].function = ft_pwd;


t_bool	is_builtins(t_cmd *builtins, t_hashtable *hashtable, t_ast *node)
{
	// char *cmds;

	
	// if (ft_strchr(node->cmds, '/') != NULL)
	// 	node->cmds = ft_strrchr(node->cmds, '/') + 1;
	// else
	
	while (builtins->name)
	{
		if (ft_strcmp(node->cmds, builtins->name) == 0)
		{
			execute_builtins(builtins, hashtable, node);
			return (true);
		}
		builtins++;
	}
	return (false);
}

void	execute_builtins(t_cmd *builtins, t_hashtable *hashtable, t_ast *node)
{
	while (builtins->name)
	{
		if (ft_strcmp(node->cmds, builtins->name) == 0)
		{
			builtins->function(hashtable, node->args);
			break ;
		}
		builtins++;
	}
}
