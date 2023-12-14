/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:43:27 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/14 17:26:39 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    handle_redirects(t_ast *node)
{
	if (node->type == TYPE_REDIRECT)
	{
		if (ft_strncmp(node->cmds, ">", 1) == 0)
			redirect_output(node, node->delim);
		else if (ft_strncmp(node->cmds, ">>", 2) == 0)
			redirect_append(node, node->delim);
		else if (ft_strncmp(node->cmds, "<", 1) == 0)
			redirect_input(node, node->delim);
	}
}

void	analyze_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node)
{		
    analyze_if_print(node, 1);
	if (node->type == TYPE_REDIRECT && node->print_redir == true)
	{
		if (ft_strncmp(node->cmds, ">", 1) == 0 || ft_strncmp(node->cmds, ">>", 2) == 0)
			simple_redirect_out(exec, hashtable, node, NULL);
		else
			simple_redirect_in(exec, hashtable, node);
	}
	else
		exec_multi_cmds(exec, hashtable, node->right);
}
