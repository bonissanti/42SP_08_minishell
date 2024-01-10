/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:02:36 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/10 18:49:43 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit(t_shell *shell, char **args)
{
	int	argc;

	shell->exit_status = 0;
	argc = ft_count_args(args);
	if (argc > 2)
	{
		ft_fprintf(2, "exit: too many arguments\n");
		if (!ft_isdigit(args[1][0]))
			shell->exit_status = 2;
		else
			shell->exit_status = 1;
	}
	else if (argc == 2)
	{
		if (!ft_isdigit(args[1][0]) && args[1][0] != '-' && args[1][0] != '+')
		{
			ft_fprintf(2, "exit: %s: numeric argument required\n", args[1]);
			shell->exit_status = 2;
		}
		if (ft_isdigit(args[1][0]) || args[1][0] == '-' || args[1][0] == '+')
			shell->exit_status = ft_atoi(args[1]) % 256;
	}
	shell->cmd_status = shell->exit_status;
	return (shell->exit_status);
}
