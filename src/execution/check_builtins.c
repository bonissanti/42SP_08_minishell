/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/14 14:38:04 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int    execute_if_builtin(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
    char *cmds;

    if (ft_strchr(node->cmds, '/') != NULL)
        cmds = ft_strrchr(node->cmds, '/') + 1;
    else
        cmds = node->cmds;

    if (ft_strcmp(cmds, "echo") == 0)
       return(ft_echo(hashtable, node->args + 1));
    else if (ft_strcmp(cmds, "cd") == 0)
       return(ft_cd(hashtable, node->args + 1));
    else if (ft_strcmp(cmds, "pwd") == 0)
       return(ft_pwd(hashtable, node->args + 1));
    else if (ft_strcmp(cmds, "export") == 0)
       return(ft_export(hashtable, node->args + 1));
    else if (ft_strcmp(cmds, "unset") == 0)
       return(ft_unset(hashtable, node->args + 1));
    else if (ft_strcmp(cmds, "env") == 0)
       return(ft_env(hashtable, node->args + 1));
    else if (ft_strcmp(cmds, "exit") == 0)
       ft_exit(hashtable, node->args + 1);
    else
        return (1);
}
