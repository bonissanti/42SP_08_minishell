/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:32:04 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 19:40:11 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_cd(t_hashtable *hashtable, char **args, int argc);

void	ft_cd(t_hashtable *hashtable, char **args)
{
	char	*oldpwd;
	char 	*pwd;
	char	*cwd;
	size_t	argc;

	argc = ft_count_args(args);
	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	oldpwd = search(hashtable, "PWD")->value;
	insert(hashtable, "OLDPWD", oldpwd);
	if (argc == 1 || argc == 2)
		handle_cd(hashtable, args, argc);
	cwd = getcwd(NULL, 0);
	insert(hashtable, "PWD", cwd);
	free(cwd);
	return ;
}

static void	handle_cd(t_hashtable *hashtable, char **args, int argc)
{
	if (argc == 1)
	{
		if (chdir(hashtable->home->value) == -1)
		{
			ft_fprintf(2, "cd: %s: %s\n", hashtable->home, strerror(errno));
			return ;
		}
	}
	else if (argc == 2)
	{
		if (chdir(args[1]) == -1)
		{
			ft_fprintf(2, "cd: %s: %s\n", args[1], strerror(errno));
			return ;
		}
	}
}
