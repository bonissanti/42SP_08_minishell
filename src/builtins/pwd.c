/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:12:58 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/10 19:14:32 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_shell *shell, char **args)
{
	char	*cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	free(cwd);
	shell->cmd_status = 0;
}
