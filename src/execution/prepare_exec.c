/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:07:07 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/04 12:55:06 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast	*find_node(t_ast *root, t_type type)
{
	if (root == NULL)
		return (NULL);
	while (root)
	{
		if (root->type == type)
			return (root);
		else if (root->right)
			root = root->right;
		else
			break ;
	}
	return (NULL);
}

int	analyze_heredoc(t_exec *exec, t_ast *node, t_hashtable *hashtable)
{
	analyze_if_print(node, 0);
	if (node->type == TYPE_HEREDOC)
		handle_heredoc(hashtable, exec, node);
	else
		exec_multi_cmds(exec, hashtable, node->right);
	return (0);
}

void	handle_error(t_ast *node, int result)
{
	if (result == 127)
	{
		g_global.cmd_status = 127;
		ft_fprintf(2, "minishell: %s: command not found\n", node->cmds);
	}
	else if (result == 126)
	{
		g_global.cmd_status = 126;
		ft_fprintf(2, "minishell: %s: %s\n", node->cmds, strerror(errno));
	}
	return ;
}
