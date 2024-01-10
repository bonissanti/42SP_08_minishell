/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:45:17 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/10 17:16:55 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signals(void)
{
	signal(SIGINT, refresh_prompt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, handle_sigpipe);
}

void	init_hd_signals(int pid)
{
	if (!pid)
		signal(SIGINT, hd_quit);
	else
		signal(SIGINT, refresh_prompt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, handle_sigpipe);
}

void	hd_quit(int signal)
{
	(void)signal;
	get_shell()->cmd_status = 130;
	ft_putendl_fd("", 1);
	close(0);
}

void	refresh_prompt(int signal)
{
	if (signal == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	exec_signals(int pid)
{
	if (pid == 0)
		signal(SIGINT, SIG_DFL);
	else
		signal(SIGINT, refresh_prompt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, handle_sigpipe);
}
