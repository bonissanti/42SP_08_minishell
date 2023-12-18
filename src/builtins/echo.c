/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:06:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 19:50:01 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_flag_n(char *arg);

void	ft_echo(t_hashtable *hashtable, char **args)
{
	int	i;
	int newline;

	i = -1;
	newline = 1;
	(void)hashtable;
	while (args[++i] != NULL)
	{
		if (args[i][0] == '$' && args[i][1] == '?')
			ft_printf("%d", g_global.cmd_status);
		else if (is_flag_n(args[i]))
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
	g_global.cmd_status = 0;
}

t_bool	is_flag_n(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[++i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
	}
	return (true);
}
