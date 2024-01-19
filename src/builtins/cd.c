/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:32:04 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/17 17:37:15 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_cd(t_shell *shell, char **args, int argc);

/**
 * Function: ft_cd
 * -----------------
 * This function is used to change the current working directory.
 *  
 * @param: *shell: The static variable that is holding all the data that
 * is being shared between the functions.
 * @param: **args: A 2d array containing the command name and its arguments.
 * 
 * @var: *oldpwd: A pointer to a string that will hold the old working directory.
 * @var: *cwd: A pointer to a string that will hold the current working directory.
 * @var: argc: An integer that holds the number of arguments.
 * 
 * @return: Returns nothing.
 *
 */

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

/**
 * Function: handle_cd
 * -----------------
 * This is a helper function of ft_cd, it is called to handle with errors
 * that happened due the info from **args 2d array.
 *  
 * @param: *shell: The static variable that is holding all the data that
 * is being shared between the functions.
 * @param: **args: A 2d array containing the command name and its arguments.
 * @param: argc: An integer that holds the number of arguments.
 * 
 * @return: Returns nothing.
 *
 */

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
