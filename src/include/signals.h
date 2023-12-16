#ifndef SIGNALS_H
# define SIGNALS_H

#include "./minishell.h"

//############################### Signals ###################################

void	init_signals(void);
void	init_hd_signals(int pid, t_hashtable *hash);
void    hd_quit(int signal);
void	refresh_prompt(int signal);
void	exec_signals(int pid);

#endif