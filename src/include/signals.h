/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:32:55 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/08 20:04:14 by aperis-p         ###   ########.fr       */
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