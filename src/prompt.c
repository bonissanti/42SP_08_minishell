/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/19 16:22:38 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"



int	prompt_validation(char *readline_input, t_hashtable *env)
{
	if (ft_strcmp(g_global.readline_input, "exit") == 0
		|| !g_global.readline_input)
	{
		free_lists();
		final_wipeout(env);
		exit(0);
	}
	if (ft_strlen(readline_input) != 0)
		return (true);
	else
		return (false);
}

static inline void	finish_prompt(t_exec exec)
{
	delete_node(g_global.ast);
	free_lists();
	restore_fd(exec.old_stdin, exec.old_stdout);
}

static void	init_global_structs(void)
{
	g_global.ast = NULL;
	g_global.cmd_list = NULL;
	g_global.cmd_status = 0;
	g_global.exit_status = -1;
	g_global.readline_input = NULL;
	g_global.readline_input_to_free = NULL;
	g_global.tkn_list = NULL;
}

void	prompt(t_hashtable *env)
{
	int		to_exec;
	t_exec	exec;

	init_global_structs();
	while (g_global.exit_status == -1)
	{
		init_signals();
		init_structs(&exec, 0, sizeof(t_exec));
		if (isatty(STDIN_FILENO))
			g_global.readline_input = readline_trash_can(readline("$ "));
		else
			g_global.readline_input = readline_trash_can(readline(""));
		if (!prompt_validation(g_global.readline_input, env))
			continue ;
		add_history(g_global.readline_input);
		tokenizer(env);
		to_exec = parser(env);
		g_global.ast = init_ast(g_global.cmd_list, &exec);
		backup_fd(&exec.old_stdin, &exec.old_stdout);
		if (to_exec != 2)
			exec_multi_cmds(&exec, env, g_global.ast);
		delete_node(g_global.ast);
		free_lists();
		restore_fd(exec.old_stdin, exec.old_stdout);
	}
	final_wipeout(env);
}
