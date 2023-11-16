/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/15 23:54:00 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void prompt(t_hashtable *env)
{
	// char *cmd;

	// cmd = NULL;
	ft_putstr_fd("$ ", 1);
	// cmd = readline("");
	// g_global.readline_input = cmd;	
	g_global.readline_input = readline("");	
	ft_printf("%s\n", g_global.readline_input);
	tokenizer(&g_global, g_global.readline_input, env);
	print_tkn_list(g_global.tkn_list);
	parser(env);
	while(ft_strcmp(g_global.readline_input, "exit") != 0)
	{
		ft_putstr_fd("$ ", 1);
		g_global.readline_input = readline("");
		tokenizer(&g_global, g_global.readline_input, env);
		print_tkn_list(g_global.tkn_list);
		parser(env);
	}
	free(g_global.readline_input);
}
