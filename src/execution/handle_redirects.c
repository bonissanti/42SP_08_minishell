/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:43:27 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/28 13:27:25 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redirects(t_ast *node)
{
	int ok_to_redirect;

	ok_to_redirect = 1;
	if (node->type == TYPE_REDIRECT)
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

int	get_index_redirect(t_ast *root, t_type type)
{
	int	index;
	static t_ast *node;

	index = -1;
	if (type == TYPE_HEREDOC)
		node = root->right;
	else
		node = root;
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

	analyze_if_print(node, 1);
	index = get_index_redirect(node, TYPE_REDIRECT);
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
	return (0);
}

// int analyze_redirect2(t_exec *exec, t_hashtable *hashtable, t_ast *node)
// {
// 	analyze_if_print(node, 1);
	
// }