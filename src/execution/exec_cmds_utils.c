/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:27:30 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/29 19:27:52 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"

void	init_stru

// void	execute_and_or(t_vector  *vtr, t_hashtable *hashtable, t_ast *node)
// {
// 	int status;
// 	pid_t pid;

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
// 		return ;
// 	}
// 	if (pid == 0)
// 	{
// 		if (!execute_if_builtin(vtr, hashtable, node->left))
// 			execve(node->left->path, node->left->args, NULL);
// 		exit(0);
// 	}
// 	else
// 	{
// 		wait(&status);
// 		if ((ft_strncmp(node->cmds, "&&", 2) == 0 && WEXITSTATUS(status) == 0) 
// 			|| (ft_strncmp(node->cmds, "||", 2) == 0 && WEXITSTATUS(status) != 0))
// 			if (!execute_if_builtin(vtr, hashtable, node->right))
// 				execve(node->right->path, node->right->args, NULL);
// 	}
// }
