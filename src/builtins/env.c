/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:19:43 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/10 19:11:57 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
