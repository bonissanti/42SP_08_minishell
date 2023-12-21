/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:32:55 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/21 14:41:00 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "./minishell.h"

//############################### Signals ###################################

void	init_signals(void);
void	init_hd_signals(int pid);
void	hd_quit(int signal);
void	refresh_prompt(int signal);
void	exec_signals(int pid);
void	sigpipe_handler(int signal);
void	handle_sigpipe(int sig);

#endif