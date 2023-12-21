/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:45:17 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/21 15:56:07 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	init_signals(void)
// {
// 	signal(SIGINT, refresh_prompt);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGPIPE, handle_sigpipe);
// }

void init_signals(void)
{
    struct sigaction sa;
    sa.sa_handler = refresh_prompt;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESETHAND;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    sa.sa_handler = handle_sigpipe;
    if (sigaction(SIGPIPE, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
}


void handle_sigpipe(int sig)
{
    pid_t pid;
    int status;
    restore_fd(STDIN_FILENO, STDOUT_FILENO);
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        ft_putendl_fd("\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
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
	if (signal == SIGINT)
	{
		free_lists();
		destroy_hashtable(g_global.hash);
		rl_clear_history();
		exit(130);
	}
}

void	refresh_prompt(int signal)
{
	if (signal == SIGINT)
	{
		ft_putendl_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	exec_signals(int pid)
// {
// 	if (pid == 0)
// 		signal(SIGINT, SIG_DFL);
// 	else
// 		signal(SIGINT, refresh_prompt);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGPIPE, handle_sigpipe);
// }

void	exec_signals(int pid)
{
	struct sigaction sa;
    sa.sa_handler = refresh_prompt;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    sa.sa_handler = handle_sigpipe;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESETHAND;
	if (sigaction(SIGPIPE, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
}
}