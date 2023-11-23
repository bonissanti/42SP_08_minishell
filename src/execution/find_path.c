/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:08:58 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 19:14:24 by brunrodr         ###   ########.fr       */
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

    temp = ft_strtok(path, ":");
    while (temp)
    {
        slash = ft_strjoin(temp, "/");
        full_path = ft_strjoin(slash, node->cmds);
        free(slash);
        if (access(full_path, F_OK) == 0)
            return (full_path);
        temp = ft_strtok(NULL, ":");
        free(full_path);
    }
    return (NULL);
}
