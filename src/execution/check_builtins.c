/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/13 17:35:45 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/hash.h"

t_bool	execute_if_builtin(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	char *cmds;

	if (ft_strchr(node->cmds, '/') != NULL)
		cmds = ft_strrchr(node->cmds, '/') + 1;
	else
		cmds = node->cmds;

	if (ft_strcmp(cmds, "echo") == 0)
		ft_echo(hashtable, node->args + 1);
	else if (ft_strcmp(cmds, "cd") == 0)
		ft_cd(hashtable, node->args + 1);
	else if (ft_strcmp(cmds, "pwd") == 0)
		ft_pwd(hashtable, node->args + 1);
	else if (ft_strcmp(cmds, "export") == 0)
		ft_export(hashtable, node->args + 1);
	else if (ft_strcmp(cmds, "unset") == 0)
		ft_unset(hashtable, node->args + 1);
	else if (ft_strcmp(cmds, "env") == 0)
		ft_env(hashtable, node->args + 1);
	else if (ft_strcmp(cmds, "exit") == 0)
		ft_exit(hashtable, node->args + 1);
	else
		return (false);
}
