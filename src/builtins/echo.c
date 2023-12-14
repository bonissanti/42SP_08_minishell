/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:06:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/14 18:59:52 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_flag_n(char *arg);

int	ft_echo(t_hashtable *hashtable, char **args)
{
	int	i;

	i = -1;
	(void)hashtable;
	while (args[++i] != NULL)
	{
		if (args[i][0] == '$' && args[i][1] == '?')
			ft_printf("%d", g_global.exit_status);
		if (args[i][0] == '-' && is_flag_n(args[i]))
			continue ;
		ft_printf("%s ", args[i]);
	}
	if (!is_flag_n(args[i - 1]))
		ft_printf("\n");
	return(0);
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
