/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:32:04 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/09 18:04:09 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>
#include <stdlib.h>

int    ft_cd(t_hashtable *hashtable, char **args)
{
	size_t argc;
	char *home;

	argc = ft_count_args(args);
	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else if (argc == 1)
		home = search(hashtable, "HOME")->value;
	else if (argc == 2)
	{
		
	}
	
}






int main()
{
	char *cd_args[] = {"cd", "../libft", NULL};
	ft_cd(cd_args);

	char *cd_args2[] = {"cd", NULL};
	ft_cd(cd_args2);

	char *cd_args3[] = {"cd", "/path/to/directory/", "with", "extra", "arguments", NULL};
	ft_cd(cd_args3);

	char *cd_args4[] = {"cd", "/path/to/directory/with/no/permissions", NULL};
	ft_cd(cd_args4);
	return (0);
}
