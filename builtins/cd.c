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

#include "minishell.h"

int    ft_cd(char **args)
{
	if (args[1] == NULL)
		ft_putstr_fd("expected argument to \"cd\"\n", 2);
	else
	{
		if (chdir(args[1]) != 0)
			perror("");
	}
	return (1);
}