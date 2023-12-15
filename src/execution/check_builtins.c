/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 16:03:24 by brunrodr         ###   ########.fr       */
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
		return (ft_echo(hashtable, node->args + 1));
	else if (ft_strcmp(cmds, "cd") == 0)
		return (ft_cd(hashtable, node->args));
	else if (ft_strcmp(cmds, "pwd") == 0)
		return (ft_pwd(hashtable, node->args));
	else if (ft_strcmp(cmds, "export") == 0)
		return (ft_export(hashtable, node->args));
	else if (ft_strcmp(cmds, "unset") == 0)
		return (ft_unset(hashtable, node->args));
	else if (ft_strcmp(cmds, "env") == 0)
		return (ft_env(hashtable, node->args + 1));
	else if (ft_strcmp(cmds, "exit") == 0)
		ft_exit(hashtable, node->args + 1);
	else
		return (1);
	return (0);
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