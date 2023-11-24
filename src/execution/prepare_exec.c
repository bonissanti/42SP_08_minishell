/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:07:07 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/24 18:55:27 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"
#include "../include/hash.h"
#include "../include/exec.h"

void	analyzing_cmd(t_hashtable *hashtable, t_ast *node)
{
	char *path;
	int result;
	
	result = verify_cmd_permissions(node->cmds);
	if (node)
	{
		if (node->type == TYPE_COMMAND)
		{
			if (ft_strchr(node->cmds, '/') != NULL && result == 0) // tratamento para caminho absoluto'
			{
				if (result == 126) // tacar isso numa função para printar erro de permissão
					ft_fprintf(2, "minishell: %s: command not found\n", node->cmds);
				else if (result == 127)
					ft_fprintf(2, "minishell: %s: %s\n", node->cmds, strerror(errno));
				return ;
			}
			else
			{
				path = search(hashtable, "PATH")->value;
				node->path = build_cmd_path(node, path);
			}	
		}
		else if (node->type == TYPE_REDIRECT && ft_strncmp(node->cmds, "<<", 2) == 0)
			handle_heredoc(hashtable, node->delim);
		else if (node->type == TYPE_REDIRECT && ft_strcmp(node->cmds, "<") == 0)
			redirect_input(node->right->cmds);
		else if (node->type == TYPE_REDIRECT && ft_strcmp(node->cmds, ">") == 0)
			redirect_output(node->right->cmds);
		else if (node->type == TYPE_REDIRECT && ft_strcmp(node->cmds, ">>") == 0)
			redirect_append(node->right->cmds);
	}
	if (node->left)
		analyzing_cmd(hashtable, node->left);
	if (node->right)
		analyzing_cmd(hashtable, node->right);
}

