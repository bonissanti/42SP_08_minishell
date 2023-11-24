/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:08:58 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/24 14:13:41 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/hash.h"
#include "../include/exec.h"
#include "../include/segments.h"

char *build_cmd_path(t_ast *node, char *path)
{
    char    *temp = NULL;
    char    *full_path;
    char    *slash;
    int     result;

    temp = ft_strtok(path, ":");
    while (temp)
    {
        slash = ft_strjoin(temp, "/");
        full_path = ft_strjoin(slash, node->cmds);
        free(slash);
        result = verify_cmd_permissions(full_path);
        if (result == 0)
            return (full_path);
        temp = ft_strtok(NULL, ":");
        free(full_path);
    }
    if (result == 126)
        ft_fprintf(2, "minishell: %s: command not found\n", node->cmds);
    else if (result == 127)
        ft_fprintf(2, "minishell: %s: %s\n", node->cmds, strerror(errno));
    return (NULL);
}
