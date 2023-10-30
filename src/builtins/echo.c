/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:06:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/30 18:57:33 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

int ft_echo(t_hashtable *hash_table, char **args)
{
	int i;
	t_hash *hash;

	i = -1;
	while (args[++i] != NULL)
	{
		if (args[i][0] == '$')
		{
			hash = search_hash(hash_table, args[i] + 1);
			if (hash != NULL)
				ft_putstr_fd(hash->value, 1);
		}
		else
			ft_putstr_fd(args[i], 1);
	}
	return (1);
}

// int main(void)
// {
// 	char *echo_args[] = {"echo", "hello", "world", NULL};
// 	ft_echo(echo_args);
// 	return 0;
// }