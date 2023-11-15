/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/14 23:03:24 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void prompt(t_hashtable *env)
{
	char *cmd;

	cmd = NULL;
	ft_putstr_fd("$ ", 1);
	cmd = readline("");
	g_global.readline_input = cmd;
	
	tokenizer(&g_global, g_global.readline_input, env);
	parser(&g_global);
	ft_printf("%s\n", cmd);
	while(ft_strcmp(cmd, "exit") != 0)
	{
		ft_putstr_fd("$ ", 1);
		cmd = readline("");
		ft_printf("%s\n", cmd);
	}
	free(cmd);	
}
