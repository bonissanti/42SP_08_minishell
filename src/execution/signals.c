/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:23:41 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/11 15:57:58 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/segments.h"
#include "../include/builtins.h"
#include "../include/exec.h"

// void	setup_sigchild(void)
// {
// 	struct sigaction	sa;
// 	sa.sa_handler = &handle_sigchild;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
// 	if (sigaction(SIGCHLD, &sa, NULL) == -1)
// 	{
// 		ft_putstr_fd("Error: sigaction\n", 2);
// 		exit(1);
// 	}	
// }

// void	handle_sigchild(int sig)
// {
// 	int saved_errno;

// 	saved_errno = errno;
// 	while (waitpid(-1, NULL, WNOHANG) > 0)
// 		;
// 	errno = saved_errno;
// }
