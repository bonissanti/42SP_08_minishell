/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:45:17 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/14 18:49:02 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signals(void)
{
	signal(SIGINT, refresh_prompt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
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