/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/11 13:53:20 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_builtin(t_shell *shell, t_ast *node)
{
	char	*cmds;

	if (ft_strchr(node->cmds, '/') != NULL)
		cmds = ft_strrchr(node->cmds, '/') + 1;
	else
		cmds = node->cmds;
	if (ft_strcmp(cmds, "echo") == 0)
		ft_echo(shell, node->args + 1);
	else if (ft_strcmp(cmds, "cd") == 0)
		ft_cd(shell, node->args);
	else if (ft_strcmp(cmds, "pwd") == 0)
		ft_pwd(shell, node->args);
	else if (ft_strcmp(cmds, "export") == 0)
		ft_export(shell, node->args);
	else if (ft_strcmp(cmds, "unset") == 0)
		ft_unset(shell, node->args);
	else if (ft_strcmp(cmds, "env") == 0)
		ft_env(shell, node->args);
	else if (ft_strcmp(cmds, "exit") == 0)
		return (ft_exit(shell, node->args));
	else
		return (1);
	return (shell->exit_status);
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
