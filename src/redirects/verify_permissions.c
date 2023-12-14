/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_permissions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:46:31 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/13 19:17:52 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		return (127);
	else if (access(cmd, X_OK) != 0)
		return (126);
	return (0);
}
