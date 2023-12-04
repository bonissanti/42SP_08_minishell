/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:35:32 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/01 19:02:18 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"
#include "../include/segments.h"

void    close_all_fds(int *fd)
{
    close(fd[0]);
	close(fd[1]);
}

void ft_printf_fd(int fd)
{
    char *line;

    line = get_next_line(fd);
    if (!line)
    {
        ft_fprintf(2, "fd didn't have any lines to print.\n");
        return ;
    }
    while(line)
    {
        ft_fprintf(2, "es: %s", line);
        line = get_next_line(fd);
    }
    ft_fprintf(2, "____________________\n");
}