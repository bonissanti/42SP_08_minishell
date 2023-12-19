/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:12:32 by allesson          #+#    #+#             */
/*   Updated: 2023/12/19 09:21:10 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void empty_trash_can(void)
{
	ft_lstclear(&g_global.readline_input_to_free, ft_delete_content);
}

char *readline_trash_can(char *readline_input)
{
	if(!g_global.readline_input_to_free)
		g_global.readline_input_to_free = ft_lstnew(readline_input);
	else
		ft_lstadd_back(&g_global.readline_input_to_free, ft_lstnew(readline_input));	
	return(readline_input);
}

void free_lists(void)
{
	free_cmd_list(g_global.cmd_list);
	g_global.cmd_list = NULL;
	free_tkn_list(g_global.tkn_list);
	g_global.tkn_list = NULL;
}

void final_wipeout(t_hashtable *env)
{
	empty_trash_can();
	rl_clear_history();
	destroy_hashtable(env);
}