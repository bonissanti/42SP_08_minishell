/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:07:07 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/27 22:56:50 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_empty_cmd(char *cmd)
{
	if (cmd == NULL)
		return (true);
	if (cmd[0] == '\0')
		return (true);
	return (false);
}

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

void	analyze_heredoc(t_exec *exec, t_ast *node, t_hashtable *hashtable)
{
	analyze_if_print(node, 0);
	if (node->type == TYPE_HEREDOC)
		handle_heredoc(hashtable, exec, node);
	else
		exec_multi_cmds(exec, hashtable, node->right);
}

int	analyze_cmd(t_hashtable *hashtable, t_ast *node)
{
	char	*path;
	int		result;
	t_hash	*search_var;
	
	if (is_empty_cmd(node->cmds))
		return (0);
	result = verify_cmd_permissions(node->cmds);
	if (ft_strchr(node->cmds, '/') != NULL && result != 0)
	{
		handle_error(node, result);
		return (result);
	}
	else if (ft_strchr(node->cmds, '/') != NULL && result == 0)
		node->path = ft_strdup(node->cmds);
	else
	{
		search_var = search(hashtable, "PATH");
		if (search_var == NULL)
			return (127);
		path = search_var->value;
		node->path = build_cmd_path(node, path);
		if (node->path == NULL && !is_builtin(node))
		{
			handle_error(node, 127);
			return (127);
		}
	}
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
