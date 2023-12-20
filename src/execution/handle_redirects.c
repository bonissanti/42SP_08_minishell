/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:43:27 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/19 10:52:19 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redirects(t_ast *node)
{
	int ok_to_redirect;

	ok_to_redirect = 1;
	if (node->type == TYPE_REDIRECT && node->left)
	{
		if (ft_strncmp(node->cmds, ">>", 2) == 0)
			ok_to_redirect = redirect_append(node, node->outfile);
		else if (ft_strncmp(node->cmds, ">", 1) == 0)
			ok_to_redirect = redirect_output(node, node->outfile);
		else if (ft_strncmp(node->cmds, "<", 1) == 0)
			ok_to_redirect = redirect_input(node, node->infile);
	}
	return (ok_to_redirect);
}

int	get_index_redirect(t_ast *node)
{
	int	index;

	index = -1;
	if (node->type == TYPE_REDIRECT && node->right
		&& node->right->type == TYPE_REDIRECT)
	{
		if (ft_strncmp(node->cmds, node->right->cmds, 1) != 0)
			index = 3;
	}
	else
	{
		if (ft_strncmp(node->cmds, ">>", 2) == 0)
			index = 0;
		else if (ft_strncmp(node->cmds, ">", 1) == 0)
			index = 1;
		else if (ft_strncmp(node->cmds, "<", 1) == 0)
			index = 2;
	}
	return (index);
}

int	analyze_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node)
{
	int	index;

	if (exec->error_call == 1)
		return (1);
	else
	{
		analyze_if_print(node, 1);
		index = get_index_redirect(node);
		if ((index == 0 || index == 1) && (node->print_redir == true))
			redirect_out(exec, hashtable, node);
		else if ((index == 2) && (node->print_redir == true))
			redirect_in(exec, hashtable, node);
		else if (index == 3)
			double_redirect(exec, hashtable, node);
		else
		{
			node->left = NULL;
			exec_multi_cmds(exec, hashtable, node->right);
		}
	}
	return (0);
}
