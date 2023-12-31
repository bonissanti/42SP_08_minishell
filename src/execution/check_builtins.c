/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/02 19:24:57 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_builtin(t_hashtable *hashtable, t_ast *node)
{
	char	*cmds;

	if (ft_strchr(node->cmds, '/') != NULL)
		cmds = ft_strrchr(node->cmds, '/') + 1;
	else
		cmds = node->cmds;
	if (ft_strcmp(cmds, "echo") == 0)
		ft_echo(hashtable, node->args + 1);
	else if (ft_strcmp(cmds, "cd") == 0)
		ft_cd(hashtable, node->args);
	else if (ft_strcmp(cmds, "pwd") == 0)
		ft_pwd(hashtable, node->args);
	else if (ft_strcmp(cmds, "export") == 0)
		ft_export(hashtable, node->args);
	else if (ft_strcmp(cmds, "unset") == 0)
		ft_unset(hashtable, node->args);
	else if (ft_strcmp(cmds, "env") == 0)
		ft_env(hashtable, node->args);
	else if (ft_strcmp(cmds, "exit") == 0)
		return (ft_exit(node->args));
	else
		return (1);
	return (g_global.exit_status);
}

t_bool	is_builtin(t_ast *node)
{
	if (ft_strcmp(node->cmds, "echo") == 0)
		return (true);
	else if (ft_strcmp(node->cmds, "cd") == 0)
		return (true);
	else if (ft_strcmp(node->cmds, "pwd") == 0)
		return (true);
	else if (ft_strcmp(node->cmds, "export") == 0)
		return (true);
	else if (ft_strcmp(node->cmds, "unset") == 0)
		return (true);
	else if (ft_strcmp(node->cmds, "env") == 0)
		return (true);
	else if (ft_strcmp(node->cmds, "exit") == 0)
		return (true);
	else
		return (false);
}
