/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:38:13 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/10 18:12:58 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}

int	main(int argc, char **argv, char **envp)
	{
	(void)argc;
	(void)argv;
	t_shell	*shell;

	shell = get_shell();
	init_hash(shell, envp);
	prompt(shell->hash);
	return (shell->exit_status);
}
