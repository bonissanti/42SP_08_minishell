/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:12:58 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/21 14:15:31 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	ft_pwd(t_hashtable *hashtable, char **args)
{
	char	*cwd;

	(void)hashtable;
	(void)args;
	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	free(cwd);
}
