/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/10 21:18:37 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int prompt_validation(char *readline_input)
{
	if(ft_strlen(readline_input))
		return(true);
	return(false);
}

void free_lists(t_tkn_list *tkn_list, t_cmd_list *cmd_list)
{
	free_tkn_list(tkn_list);
	g_global.tkn_list = NULL;
	free_cmd_list(cmd_list);
	g_global.cmd_list = NULL;
}

void prompt(t_hashtable *env)
{
	(void)env;
	while(!prompt_validation(g_global.readline_input))
		g_global.readline_input = readline("$ ");
	add_history(g_global.readline_input);
	// rl_on_new_line();
	// rl_replace_line("new line", 0);
	tokenizer(&g_global, g_global.readline_input, env);
	print_tkn_list(g_global.tkn_list);
	parser(env);
	free_lists(g_global.tkn_list, g_global.cmd_list);
	while(ft_strcmp(g_global.readline_input, "exit") != 0)
	{
		free(g_global.readline_input);
		g_global.readline_input = NULL;
		while(!prompt_validation(g_global.readline_input))
			g_global.readline_input = readline("$ ");
		add_history(g_global.readline_input);
		// rl_on_new_line();
		// rl_replace_line("new line", 0);
		tokenizer(&g_global, g_global.readline_input, env);
		print_tkn_list(g_global.tkn_list);
		parser(env);
		free_lists(g_global.tkn_list, g_global.cmd_list);
	}
}
