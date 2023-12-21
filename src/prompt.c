/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/21 12:34:47 by brunrodr         ###   ########.fr       */
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
		if (isatty(STDIN_FILENO))
			g_global.readline_input = readline_trash_can(readline("$ "));
		else
			g_global.readline_input = readline_trash_can(readline(""));
		if (!prompt_validation(g_global.readline_input, env))
			continue ;
		add_history(g_global.readline_input);
		tokenizer(env);
		parser(env);
		g_global.ast = init_ast(g_global.cmd_list, &exec);
		backup_fd(&exec.old_stdin, &exec.old_stdout);
		if (g_global.to_exec != 2)
			exec_multi_cmds(&exec, env, g_global.ast);
		delete_node(g_global.ast);
		free_lists();
		restore_fd(exec.old_stdin, exec.old_stdout);
	}
	final_wipeout(env);
}

// echo "test" : test
// echo 'test' : test
// echo "$USER" : allesson
// echo '$USER' : $USER
// echo "'"USER"'" : 'USER'
// echo ""'"USER"'"" : "USER"
// echo "'"$USER"'" : 'allesson'
// echo ""'"$USER"'"" : "$USER"
// echo test "'">USER"'" : cat USER' : test '
// echo"$USER" : bash: echoallesson: command not found             FAIL
// echo"$USER: > " : bash: $'echoallesson\n': command not found    FAIL
// echo *.c : *.c
// echo ~.c : ~.c 												   FAIL
// echo ~/.c : /home/allesson/.c
// echo ./*.c : ./*.c											   result is right but printing two times
// echo "'>FILE'" : '>FILE'
// echo "'''>FILE'''" : '''>FILE'''
// echo "'''">FILE"'''" : cat FILE''' : '''
// echo ''' : > 												   FAIL "minishell: syntax error: unexpected EOF"



