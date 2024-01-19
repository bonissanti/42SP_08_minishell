/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:02:36 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/17 21:02:45 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: handle_number
 * -----------------
 * Our builtin implementation of the original env function.
 *  
 * @param: *shell: The static variable that is holding all the data that
 * is being shared between the functions.
 * @param: **args: A 2d array containing the command name and its arguments.
 * 
 * @var: num: Will hold the converted number from the string. 
 * 
 * @return: Returns nothing.
 *
 */

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

/**
 * Function: ft_exit
 * -----------------
 * Our builtin implementation of the original exit function.
 *  
 * @param: *shell: The static variable that is holding all the data that
 * is being shared between the functions.
 * @param: **args: A 2d array containing the command name and its arguments.
 * 
 * @var: argc: Will hold the amount of arguments that the 2d array **args has. 
 * 
 * @return: Returns the exit status accordingly with the arguments.
 *
 */

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
