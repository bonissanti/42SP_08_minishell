/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:32:04 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/19 19:06:36 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

int    ft_cd(char **args)
{
	if (args[1] == NULL)
		printf("expected argument to \"cd\"\n");
	else
	{
		if (chdir(args[1]) != 0)
			perror("");
	}
	return (1);
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
