/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:06:42 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/09 13:08:29 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(t_hashtable *hashtable, char **args)
{
	int		i;
	int		newline;
	char	*temp;

	temp = *args;
	i = -1;
	newline = 1;
	(void)hashtable;
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
	g_global.cmd_status = 0;
}
