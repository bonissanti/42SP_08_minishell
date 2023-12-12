/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/12 17:18:52 by allesson         ###   ########.fr       */
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
	int pid;
	
	// while(!prompt_validation(g_global.readline_input))
	// 	g_global.readline_input = readline("$ ");
	// add_history(g_global.readline_input);
	// // rl_on_new_line();
	// // rl_replace_line("new line", 0);
	// tokenizer(&g_global, g_global.readline_input, env);
	// print_tkn_list(g_global.tkn_list);
	// parser(env);
	// root = init_ast(g_global.cmd_list, &vtr.exec, env);
	// free_lists(g_global.tkn_list, g_global.cmd_list);
	// backup_fd(&vtr.exec.old_stdin, &vtr.exec.old_stdout);
    // exec_multi_cmds(&vtr, env, root);
	// restore_fd(vtr.exec.old_stdin, vtr.exec.old_stdout);
	g_global.readline_input = NULL;
	while(ft_strcmp(g_global.readline_input, "exit") != 0)
	{
		while(!prompt_validation(g_global.readline_input))
			g_global.readline_input = readline("$ ");
		add_history(g_global.readline_input);
		// rl_on_new_line();
		// rl_replace_line("new line", 0);
		tokenizer(&g_global, g_global.readline_input, env);
		print_tkn_list(g_global.tkn_list);
		parser(env);
		root = init_ast(g_global.cmd_list, &vtr.exec, env);
		free_lists(g_global.tkn_list, g_global.cmd_list);
		backup_fd(&vtr.exec.old_stdin, &vtr.exec.old_stdout);
		pid = fork();
		if(!pid)
			exec_multi_cmds(&vtr, env, root);
		else
		{
			wait(NULL);	
			restore_fd(vtr.exec.old_stdin, vtr.exec.old_stdout);
			free(g_global.readline_input);
			g_global.readline_input = NULL;
		}
	}
	delete_node(root);
    destroy_hashtable(env);
}
