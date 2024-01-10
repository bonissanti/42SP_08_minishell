/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:43:27 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/10 17:56:07 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redirects(t_ast *node)
{
	int	ok_to_redirect;

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
	int				index;
	static t_ast	*node;

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
		else if (*node->cmds == '>')
			index = 1;
		else if (*node->cmds == '<')
			index = 2;
	}
	return (index);
}

int	analyze_redirect(t_exec *exec, t_shell *shell, t_ast *node)
{
	int	ok_to_create;

	ok_to_create = create_files(node, exec, 0);
	if ((ok_to_create == 1 || ok_to_create == -1) && exec->count_pipes == 0)
		return (1);
	simple_redirect(exec, shell, node);
	return (0);
}
