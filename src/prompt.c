/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/14 19:17:04 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int prompt_validation(char *readline_input)
{
	if(ft_strlen(readline_input) != 0)
		return(true);
	else if (ft_strcmp(g_global.readline_input, "exit") == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else
		return(false);
}

void free_lists(t_tkn_list *tkn_list, t_cmd_list *cmd_list)
{
	free_tkn_list(tkn_list);
	g_global.tkn_list = NULL;
	free_cmd_list(cmd_list);
	g_global.cmd_list = NULL;
}

void prompt(t_hashtable *env, t_exec exec)
{
	t_ast *root;

	g_global.readline_input = NULL;
	while(g_global.exit_status == 0)
	{
		while(!prompt_validation(g_global.readline_input))
			g_global.readline_input = readline("$ ");
		add_history(g_global.readline_input);
		tokenizer(&g_global, g_global.readline_input, env);
		parser(env);
		root = init_ast(g_global.cmd_list, &exec, env);
		backup_fd(&exec.old_stdin, &exec.old_stdout);
		exec_multi_cmds(&exec, env, root);
		free_lists(g_global.tkn_list, g_global.cmd_list);
		restore_fd(exec.old_stdin, exec.old_stdout);
		free(g_global.readline_input);
		g_global.readline_input = NULL;
	}
	delete_node(root);
    destroy_hashtable(env);
}
