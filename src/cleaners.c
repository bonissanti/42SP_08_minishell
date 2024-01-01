/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:12:32 by allesson          #+#    #+#             */
/*   Updated: 2023/12/30 14:30:13 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	empty_trash_can(void)
{
	ft_lstclear(&g_global.readline_input_to_free, ft_delete_content);
}

char	*readline_trash_can(char *readline_input)
{
	if (!g_global.readline_input_to_free)
		g_global.readline_input_to_free = ft_lstnew(readline_input);
	else
		ft_lstadd_back(&g_global.readline_input_to_free,
			ft_lstnew(readline_input));
	return (readline_input);
}

void	free_lists(void)
{
	if (g_global.cmd_list)
	{
		free_cmd_list(g_global.cmd_list);
		g_global.cmd_list = NULL;
	}
	if (g_global.tkn_list)
	{
		free_tkn_list(g_global.tkn_list);
		g_global.tkn_list = NULL;
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
	delete_node(g_global.ast);
	destroy_hashtable(env);
	free_lists();
	empty_trash_can();
	restore_fd(exec->old_stdin, exec->old_stdout);
}
