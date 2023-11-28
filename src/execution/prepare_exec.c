/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:07:07 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/27 17:17:21 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"
#include "../include/hash.h"
#include "../include/exec.h"

void	analyzing_cmd(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	char *path;
	int result;
	
	if (node)
	{
		if (node->type == TYPE_COMMAND)
		{
			result = verify_cmd_permissions(node->cmds);
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
		if (node->type == TYPE_REDIRECT)
			is_redirect(vtr, hashtable, node);
	}
	if (node->left)
		analyzing_cmd(vtr, hashtable, node->left);
	if (node->right)
		analyzing_cmd(vtr, hashtable, node->right);
}

