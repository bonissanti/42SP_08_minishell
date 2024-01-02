/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:01:56 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/02 13:01:57 by brunrodr         ###   ########.fr       */
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

int	handle_slash(t_ast *node, int result)
{
	if (result != 0)
	{
		handle_error(node, result);
		return (result);
	}
	node->path = ft_strdup(node->cmds);
	return (0);
}

int	handle_no_slash(t_hashtable *hash, t_ast *node)
{
	t_hash	*search_var;
	char	*path;

	search_var = search(hash, "PATH");
	if (search_var == NULL)
		return (127);
	path = search_var->value;
	node->path = build_cmd_path(node, path);
	if (node->path == NULL && !is_builtin(node))
	{
		handle_error(node, 127);
		return (127);
	}
	return (0);
}

int	analyze_cmd(t_hashtable *hashtable, t_ast *node)
{
	int	result;

	if (is_empty_cmd(node->cmds))
		return (0);
	result = verify_cmd_permissions(node->cmds);
	if (ft_strchr(node->cmds, '/') != NULL)
		result = handle_slash(node, result);
	else
		result = handle_no_slash(hashtable, node);
	return (0);
}
