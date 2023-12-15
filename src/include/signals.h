#ifndef SIGNALS_H
# define SIGNALS_H

#include "./minishell.h"

//############################### Signals ###################################

void	init_signals(void);
void	refresh_prompt(int signal);

#endif