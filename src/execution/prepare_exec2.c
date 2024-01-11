/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:01:56 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/11 13:55:05 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_empty_cmd(char *cmd)
{
	if (cmd == NULL)
	{
		ft_fprintf(2, "Command '' not found, but can be installed with:\n");
		ft_fprintf(2, "\n");
		ft_fprintf(2, "apt install mailutils-mh  # version 1:3.7-2.1, or\n");
		ft_fprintf(2, "apt install meshio-tools  # version 4.0.4-1\n");
		ft_fprintf(2, "apt install mmh           # version 0.4-2\n");
		ft_fprintf(2, "apt install nmh           # version 1.7.1-6\n");
		ft_fprintf(2, "apt install termtris      # version 1.3-1\n");
		ft_fprintf(2, "\n");
		ft_fprintf(2, "Ask your administrator to install one of them.\n");
		ft_fprintf(2, "\n");
		return (true);
	}
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
	{
		ft_fprintf(2, "minishell: %s: command not found\n", node->cmds);
		return (127);
	}
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
	result = 0;
	result = verify_cmd_permissions(node->cmds);
	if (ft_strchr(node->cmds, '/') != NULL)
		result = handle_slash(node, result);
	else
		result = handle_no_slash(hashtable, node);
	return (result);
}

char	**hashtable_to_envp(t_hashtable *hashtable)
{
	char	**envp;
	int		i;
	int		j;
	t_hash	*curr;
	char	*temp;

	envp = (char **)malloc((hashtable->num_keys + 1) * sizeof(char *));
	j = -1;
	i = 0;
	while (++j < 101)
	{
		curr = hashtable->buckets[j];
		while (curr != NULL)
		{
			temp = ft_strjoin(curr->key, "=");
			if (curr->value)
				envp[i++] = ft_strjoin(temp, curr->value);
			else
				envp[i++] = ft_strdup("");
			free(temp);
			curr = curr->next;
		}
	}
	envp[i] = NULL;
	return (envp);
}
