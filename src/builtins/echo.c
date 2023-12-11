/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:06:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 12:37:41 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/hash.h"

t_bool	is_flag_n(char *arg);

void	ft_echo(t_hashtable *hashtable, char **args)
{
	int	i;

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
