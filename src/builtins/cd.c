/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:32:04 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/10 18:58:45 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <errno.h>

int	ft_cd(t_hashtable *hashtable, char **args)
{
	size_t	argc;
	char	*home;

	argc = ft_count_args(args);
	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else if (argc == 1)
	{
		home = search(hashtable, "HOME")->value;
		if (chdir(home) == -1)
		{
			ft_fprintf(2, "cd: %s: %s\n", home, strerror(errno));
			return (1);
		}
	}
	else if (argc == 2)
	{
		if (chdir(args[1]) == -1)
		{
			ft_fprintf(2, "cd: %s: No such file or directory\n", args[1]);
			return (1);
		}
	}
	return (0);
}







