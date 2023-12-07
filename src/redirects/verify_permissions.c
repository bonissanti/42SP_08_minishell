/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_permissions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:46:31 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 18:46:51 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/segments.h"
#include "../include/exec.h"

t_bool	verify_file_permissions(const char *file)
{
	if (access(file, F_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
		return (false);
	}
	else if (access(file, R_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
		return (false);
	}
	else if (access(file, W_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
		return (false);
	}
	return (true);
}

int	verify_cmd_permissions(const char *cmd)
{
	if (access(cmd, F_OK) != 0)
	{
		ft_fprintf(2, "minishell: command not found: %s\n", cmd);
		return (126);
	}
	else if (access(cmd, X_OK) != 0)
	{
		ft_fprintf(2, "minishell: denied permission: %s\n", cmd);
		return (127);
	}
	return (0);
}
