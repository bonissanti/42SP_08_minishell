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

// void	analyzing_cmd(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
// {
// 	char *path;
// 	int result;
	
// 	if (node)
// 	{
// 		if (node->type == TYPE_COMMAND)
// 		{
// 			result = verify_cmd_permissions(node->cmds);
// 			if (ft_strchr(node->cmds, '/') != NULL && result == 0) // tratamento para caminho absoluto'
// 			{
// 				if (result == 126) // tacar isso numa função para printar erro de permissão
// 					ft_fprintf(2, "minishell: %s: command not found\n", node->cmds);
// 				else if (result == 127)
// 					ft_fprintf(2, "minishell: %s: %s\n", node->cmds, strerror(errno));
// 				return ;
// 			}
// 			else
// 			{
// 				path = search(hashtable, "PATH")->value;
// 				node->path = build_cmd_path(node, path);
// 			}
// 		}
// 		if (node->type == TYPE_REDIRECT)
// 			handle_redirect(vtr, hashtable, node);
// 	}
// 	if (node->left)
// 		analyzing_cmd(vtr, hashtable, node->left);
// 	if (node->right)
// 		analyzing_cmd(vtr, hashtable, node->right);
// }

void	backup_fd(int *old_stdin, int *old_stdout)
{
	*old_stdin = dup(STDIN_FILENO);
	*old_stdout = dup(STDOUT_FILENO);
}

void	swap_fd(int new_fd, int system_fd)
{
	dup2(new_fd, system_fd);
	close(new_fd);
}

void	restore_fd(int reset_stdin, int reset_stdout)
{
	dup2(reset_stdin, STDIN_FILENO);
	dup2(reset_stdout, STDOUT_FILENO);
	close(reset_stdin);
	close(reset_stdout);
}