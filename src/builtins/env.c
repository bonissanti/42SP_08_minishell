/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:19:43 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/17 19:55:42 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: ft_env
 * -----------------
 * Our builtin implementation of the original env function.
 *  
 * @param: *shell: The static variable that is holding all the data that
 * is being shared between the functions.
 * @param: **args: A 2d array containing the command name and its arguments.
 * 
 * @var: i: An integer that is used to iterate through the arguments. 
 * @var: argc: Will hold the amount of arguments that the 2d array **args has.
 * @var: **keys: A 2d array to hold the keys.
 * @var: *value: A pointer to hold the current key value.
 * 
 * @return: Returns nothing.
 *
 */

void	ft_env(t_shell *shell, char **args)
{
	int		i;
	int		argc;
	char	**keys;
	char	*value;

	i = 0;
	argc = ft_count_args(args);
	keys = copy_all_keys(shell->hash);
	if (argc > 1)
	{
		ft_fprintf(2, "env: %s: No such file or directory\n", args[1]);
		shell->cmd_status = 127;
	}
	while (++i < shell->hash->num_keys)
	{
		value = search(shell->hash, keys[i])->value;
		if (value != NULL)
			ft_fprintf(1, "%s=%s\n", keys[i], value);
	}
	free(keys);
	shell->cmd_status = 0;
}
