/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_permissions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:46:31 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/11 11:00:00 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	verify_file_permissions(const char *file)
{
	t_shell	*shell;

	shell = get_shell();
	if (access(file, F_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
		shell->cmd_status = 1;
		return (false);
	}
	else if (access(file, R_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
		shell->cmd_status = 1;
		return (false);
	}
	else if (access(file, W_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
		shell->cmd_status = 1;
		return (false);
	}
	return (true);
}

int	verify_cmd_permissions(const char *cmd)
{
	if (access(cmd, F_OK) != 0)
		return (127);
	else if (access(cmd, X_OK) != 0)
		return (126);
	return (0);
}
