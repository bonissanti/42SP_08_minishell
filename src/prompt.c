/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:50:27 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/12 23:01:59 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	prompt_validation(char *readline_input, t_hashtable *env)
{
	t_shell	*shell;

	shell = get_shell();
	if (ft_strcmp(shell->readline_input, "exit") == 0
		|| !shell->readline_input)
	{
		ft_putstr_fd("exit\n", 1);
		free_lists();
		final_wipeout(env);
		exit(0);
	}
	if (!ft_strchr(shell->readline_input, 32)
		&& readline_input[ft_strlen(shell->readline_input) - 1] == '=')
		return (false);
	else if (ft_strlen(readline_input) != 0)
		return (true);
	else
		return (false);
}

static void	init_shell(t_shell *set)
{
	set->ast = NULL;
	set->cmd_list = NULL;
	set->cmd_status = 0;
	set->exit_status = -1;
	set->readline_input = NULL;
	set->readline_input_to_free = NULL;
	set->tkn_list = NULL;
	set->to_exec = 0;
}

void	prompt(t_hashtable *env)
{
	t_exec	exec;
	t_shell	*shell;

	shell = get_shell();
	init_shell(shell);
	while (shell->exit_status == -1)
	{
		init_signals();
		shell->to_exec = 0;
		init_structs(&exec, 0, sizeof(t_exec));
		shell->readline_input = gb_to_free(readline(YELLOW"$ "RESET), shell);
		if (!prompt_validation(shell->readline_input, env))
			continue ;
		add_history(shell->readline_input);
		tokenizer(shell);
		parser(env, shell);
		shell->ast = init_ast(shell->cmd_list, &exec);
		backup_fd(&exec.old_stdin, &exec.old_stdout);
		if (shell->to_exec != 2)
			exec_multi_cmds(&exec, shell->ast, shell);
		(delete_node(shell->ast), free_lists());
		restore_fd(exec.old_stdin, exec.old_stdout);
		close_all_fds();
	}
	final_wipeout(env);
}
