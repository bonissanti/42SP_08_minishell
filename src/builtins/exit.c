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

static void	handle_number(t_shell *shell, char **args)
{
	long int	num;

	num = ft_atol(args[1]);
	if (!ft_isdigit(args[1][0]) && args[1][0] != '-' && args[1][0] != '+')
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", args[1]);
		shell->exit_status = 2;
	}
	else if (num < -2147483647 || num > 2147483647)
	{
		ft_fprintf(2, "exit: %s: is not a valid integer\n", args[1]);
		shell->exit_status = 2;
	}
	else
	{
		if (num > 255)
			shell->exit_status = 255;
		else
			shell->exit_status = num;
	}
}

int	ft_exit(t_shell *shell, char **args)
{
	int			argc;

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
		handle_number(shell, args);
	shell->cmd_status = shell->exit_status;
	return (shell->exit_status);
}
