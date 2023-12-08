/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:35:32 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 18:41:02 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"
#include "../include/segments.h"

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



// void    execute_pipes2(t_hashtable *hashtable, t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
// {
//     node->pid = fork();
//     if (node->pid == 0)
//     {
//         if (*prev_pipe != -1)
//         {
//             dup2(prev_pipe[0], STDIN_FILENO);
//             close(prev_pipe[0]);
//             close(prev_pipe[1]);
//         }
//         if (*next_pipe != -1 && exec->count_pipes >= 1)
//         {
//             dup2(next_pipe[1], STDOUT_FILENO);
//             close(next_pipe[0]);
//             // close(next_pipe[1]);
//         }
//         execute_forked_command(hashtable, node);
//         exit(EXIT_SUCCESS);
//     }
//     else
//     {
//         wait (NULL);
//         if (prev_pipe && !next_pipe)
//             close(prev_pipe[1]);

//         if (next_pipe && exec->count_pipes >= 1)
//             close(next_pipe[1]);
//     }
// }
