/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:06:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/10 20:19:38 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool is_flag_n(char *arg);

void ft_echo(t_hashtable *hashtable, char **args)
{
	int i;
	
	i = -1;
	(void)hashtable;
	while (args[++i] != NULL)
	{
		if (args[i][0] == '-' && is_flag_n(args[i]))
			continue ;
		ft_printf("%s ", args[i]);
	}
	if (!is_flag_n(args[i - 1]))
		ft_printf("\n");
}

t_bool is_flag_n(char *arg)
{
	size_t i;

	i = 0;
	while (arg[++i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
	}
	return (true);
}
