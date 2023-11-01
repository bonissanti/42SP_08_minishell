/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2023/10/31 19:45:02 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void prompt(void)
{
	char *cmd;

	cmd = NULL;
	ft_putstr_fd("$ ", 1);
	cmd = readline("");
	global.readline_input = cmd;
	tokenizer(&global, global.readline_input);
	ft_printf("%s\n", cmd);
	while(ft_strcmp(cmd, "exit") != 0)
	{
		ft_putstr_fd("$ ", 1);
		cmd = readline("");
		ft_printf("%s\n", cmd);
	}
	free(cmd);	
}
