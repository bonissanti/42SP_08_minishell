/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:06:42 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/10 19:11:29 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
