/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/17 20:07:13 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include <termios.h>

int prompt_validation(char *readline_input, t_hashtable *env)
{
	if (ft_strcmp(g_global.readline_input, "exit") == 0)
	{
		free_lists();
		rl_clear_history();
    	destroy_hashtable(env);
		exit(0);
	}
	if(ft_strlen(readline_input) != 0)
		return(true);
	else
		return(false);
}

void free_lists(void)
{
	delete_node(g_global.ast);
	g_global.ast = NULL;
	free_cmd_list(g_global.cmd_list);
	g_global.cmd_list = NULL;
	free_tkn_list(g_global.tkn_list);
	g_global.tkn_list = NULL;
	free(g_global.readline_input);
	g_global.readline_input = NULL;
}

void prompt(t_hashtable *env, t_exec exec)
{
	int to_exec;

	g_global.readline_input = NULL;
	g_global.exit_status = -1;
	while(g_global.exit_status == -1)
	{
		init_signals();
    	init_structs(&exec, 0, sizeof(t_exec));
		while(!prompt_validation(g_global.readline_input, env))
			g_global.readline_input = readline("$ ");
		add_history(g_global.readline_input);
		tokenizer(env);
		to_exec = parser(env);
		g_global.ast = init_ast(g_global.cmd_list, &exec);
		backup_fd(&exec.old_stdin, &exec.old_stdout);
		if (to_exec != 2)
			exec_multi_cmds(&exec, env, g_global.ast);
		free_lists();
		restore_fd(exec.old_stdin, exec.old_stdout);
		g_global.readline_input = NULL;
	}
    destroy_hashtable(env);
}
