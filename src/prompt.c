/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/11 17:13:37 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

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

void prompt(t_hashtable *env, t_vector vtr)
{
	t_ast *root;
	
	while(!prompt_validation(g_global.readline_input))
		g_global.readline_input = readline("$ ");
	add_history(g_global.readline_input);
	// rl_on_new_line();
	// rl_replace_line("new line", 0);
	tokenizer(&g_global, g_global.readline_input, env);
	print_tkn_list(g_global.tkn_list);
	parser(env);
	root = init_ast(g_global.cmd_list, &vtr.exec);
	free_lists(g_global.tkn_list, g_global.cmd_list);
	backup_fd(&vtr.exec.old_stdin, &vtr.exec.old_stdout);
    exec_multi_cmds(&vtr, env, root);
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
		root = init_ast(g_global.cmd_list, &vtr.exec);
		free_lists(g_global.tkn_list, g_global.cmd_list);
		backup_fd(&vtr.exec.old_stdin, &vtr.exec.old_stdout);
    	exec_multi_cmds(&vtr, env, root);
	}
	delete_node(root);
    destroy_hashtable(env);
}
