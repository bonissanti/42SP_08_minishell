/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:32:04 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/10 19:51:38 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_cd(t_shell *shell, char **args, int argc);

void	ft_cd(t_shell *shell, char **args)
{
	char	*oldpwd;
	char	*cwd;
	size_t	argc;

	argc = ft_count_args(args);
	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		shell->cmd_status = 1;
		return ;
	}
	oldpwd = search(shell->hash, "PWD")->value;
	insert(shell->hash, "OLDPWD", oldpwd);
	if (argc == 1 || argc == 2)
		handle_cd(shell, args, argc);
	cwd = getcwd(NULL, 0);
	insert(shell->hash, "PWD", cwd);
	free(cwd);
	return ;
}

static void	handle_cd(t_shell *shell, char **args, int argc)
{
	if (argc == 1)
	{
		if (shell->hash->home == NULL)
		{
			ft_fprintf(2, "cd: HOME not set\n");
			shell->cmd_status = 1;
			return ;
		}
		if (chdir(shell->hash->home->value) == -1)
		{
			ft_fprintf(2, "cd: %s\n", strerror(errno));
			shell->cmd_status = 1;
			return ;
		}
	}
	else if (argc == 2)
	{
		if (chdir(args[1]) == -1)
		{
			ft_fprintf(2, "cd: %s: %s\n", args[1], strerror(errno));
			shell->cmd_status = 1;
			return ;
		}
	}
}
