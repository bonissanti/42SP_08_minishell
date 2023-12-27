/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:06:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/27 11:16:04 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_flag_n(char *arg);

void	ft_echo(t_hashtable *hashtable, char **args)
{
	int	i;
	int	newline;
	char *temp = *args;

	i = -1;
	newline = 1;
	(void)hashtable;
	while (args[++i] != NULL)
	{
		if (args[i][0] == '$' && args[i][1] == '?')
		{
			ft_printf("%d", g_global.cmd_status);
			*args = (*args + 2);
		}
		
		if (is_flag_n(args[i]))
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

t_bool	is_flag_n(char *arg)
{
	size_t	i;

	i = 1;
	if (arg[0] != '-')
		return (false);
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}
