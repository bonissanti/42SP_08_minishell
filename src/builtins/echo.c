/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:06:42 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/17 17:39:52 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: ft_echo
 * -----------------
 * Our builtin implementation of the original echo function.
 *  
 * @param: *shell: The static variable that is holding all the data that
 * is being shared between the functions.
 * @param: **args: A 2d array containing the command name and its arguments.
 * 
 * @var: i: An integer that is used to iterate through the arguments. 
 * @var: newline: An integer that is used to check if the -n flag was passed.
 * 
 * @return: Returns nothing.
 *
 */

void	ft_echo(t_shell *shell, char **args)
{
	int		i;
	int		newline;
	char	*temp;

	temp = *args;
	i = -1;
	newline = 1;
	while (args[++i] != NULL)
	{
		if (!ft_strncmp(args[i], "-n", 2))
			newline = 0;
		else
		{
			ft_printf("%s", args[i]);
			if (args[i + 1] != NULL)
				ft_printf(" ");
		}
	}
	if (newline)
		ft_printf("\n");
	*args = temp;
	shell->cmd_status = 0;
}
