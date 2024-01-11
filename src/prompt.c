/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/10 21:32:53 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	prompt_validation(char *readline_input, t_hashtable *env)
{
	if (ft_strcmp(g_global.readline_input, "exit") == 0
		|| !g_global.readline_input)
	{
		ft_putstr_fd("exit\n", 1);
		free_lists();
		final_wipeout(env);
		exit(0);
	}
	if (!ft_strchr(g_global.readline_input, 32)
		&& readline_input[ft_strlen(g_global.readline_input) - 1] == '=')
		return (false);
	else if (ft_strlen(readline_input) != 0)
		return (true);
	else
		return (false);
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
	g_global.to_exec = 0;
}

void	prompt(t_hashtable *env)
{
	t_exec	exec;

	init_global_structs();
	while (g_global.exit_status == -1)
	{
		init_signals();
		g_global.to_exec = 0;
		init_structs(&exec, 0, sizeof(t_exec));
		g_global.readline_input = gb_to_free(readline(YELLOW"$ "RESET));
		if (!prompt_validation(g_global.readline_input, env))
			continue ;
		add_history(g_global.readline_input);
		tokenizer(env);
		parser(env);
		g_global.ast = init_ast(g_global.cmd_list, &exec);
		backup_fd(&exec.old_stdin, &exec.old_stdout);
		exec_multi_cmds(&exec, env, g_global.ast);
		(delete_node(g_global.ast), free_lists());
		restore_fd(exec.old_stdin, exec.old_stdout);
		close_all_fds();
	}
	final_wipeout(env);
}
