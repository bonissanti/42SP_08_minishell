/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:43:27 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 19:05:05 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_redirects(t_ast *node)
{
	if (node->type == TYPE_REDIRECT)
	{
		if (ft_strncmp(node->cmds, ">", 1) == 0)
			redirect_output(node, node->outfile);
		else if (ft_strncmp(node->cmds, ">>", 2) == 0)
			redirect_append(node, node->outfile);
		else if (ft_strncmp(node->cmds, "<", 1) == 0)
			redirect_input(node, node->infile);
	}
}

void	analyze_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node)
{
	t_bool	rdir_in;
	t_bool	rdir_out;

	rdir_in = false;
	rdir_out = false;
	analyze_if_print(node, 1);
	if (node->type == TYPE_REDIRECT && node->right
		&& node->right->type == TYPE_REDIRECT)
	{
		if (ft_strncmp(node->cmds, node->right->cmds, 1) != 0)
		{
			rdir_in = true;
			rdir_out = true;
		}
	}
	if (rdir_in && rdir_out)
		double_redirect(exec, hashtable, node);
	else if (node->type == TYPE_REDIRECT && node->print_redir == true)
		simple_redirect(exec, hashtable, node);
	else
	{
		node->left = NULL;
		exec_multi_cmds(exec, hashtable, node->right);
	}
}
