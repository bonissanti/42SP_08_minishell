/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:12:58 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/10 20:49:10 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_hashtable *hashtable, char **args)
{
	char *cwd;
	// char *old_pwd;

	(void)hashtable;
	(void)args;
	// old_pwd = getenv("OLDPWD");	
	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	free(cwd);
}
