/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/22 16:19:38 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./parser/hash.h"
#include "./parser/parser.h"

int prompt_validation(char *readline_input)
{
	if(ft_strlen(readline_input))
		return(true);
	return(false);
}

void prompt(t_hashtable *env)
{
	(void)env;
	while(!prompt_validation(g_global.readline_input))
		g_global.readline_input = readline("$ ");
	add_history(g_global.readline_input);
	tokenizer(&g_global, g_global.readline_input, env);
	print_tkn_list(g_global.tkn_list);
	parser(env);
	free_tkn_list(g_global.tkn_list);
	g_global.tkn_list = NULL;
	free_cmd_list(g_global.cmd_list);
	g_global.cmd_list = NULL;
	while(ft_strcmp(g_global.readline_input, "exit") != 0)
	{
		free(g_global.readline_input);
		g_global.readline_input = NULL;
		while(!prompt_validation(g_global.readline_input))
			g_global.readline_input = readline("$ ");
		add_history(g_global.readline_input);		
		tokenizer(&g_global, g_global.readline_input, env);
		print_tkn_list(g_global.tkn_list);
		parser(env);
		free_tkn_list(g_global.tkn_list);
		g_global.tkn_list = NULL;
		free_cmd_list(g_global.cmd_list);
		g_global.cmd_list = NULL;
	}
}
