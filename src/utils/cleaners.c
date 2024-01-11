/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:12:32 by allesson          #+#    #+#             */
/*   Updated: 2024/01/11 11:03:09 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	empty_trash_can(void)
{	
	t_shell	*shell;

	shell = get_shell();
	ft_lstclear(&shell->readline_input_to_free, ft_delete_content);
}

char	*gb_to_free(char *readline_input, t_shell *shell)
{	
	if (!shell->readline_input_to_free)
		shell->readline_input_to_free = ft_lstnew(readline_input);
	else
		ft_lstadd_back(&shell->readline_input_to_free,
			ft_lstnew(readline_input));
	return (readline_input);
}

void	free_lists(void)
{
	t_shell	*shell;

	shell = get_shell();
	if (shell->cmd_list)
	{
		free_cmd_list(shell->cmd_list);
		shell->cmd_list = NULL;
	}
	if (shell->tkn_list)
	{
		free_tkn_list(shell->tkn_list);
		shell->tkn_list = NULL;
	}
}

void	final_wipeout(t_hashtable *env)
{
	empty_trash_can();
	rl_clear_history();
	destroy_hashtable(env);
}

void	free_for_finish(t_exec *exec, t_hashtable *env)
{
	delete_node(get_shell()->ast);
	destroy_hashtable(env);
	free_lists();
	empty_trash_can();
	restore_fd(exec->old_stdin, exec->old_stdout);
}
