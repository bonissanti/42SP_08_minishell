/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:40:02 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 19:14:54 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"


void    pipe_from_redirect(t_hashtable *hash, t_vector *vtr, t_ast *node, int *prev_pipe)
{
    int next_pipe[2] = {-1, -1};

    pipe(next_pipe);
    if (node == NULL)
        return ;

    if (vtr->exec.count_pipes == 0) // pensado para caso cat < outfile.txt | wc
    {
        ft_printf_fd(prev_pipe[0]);
        execute_pipes(hash, &vtr->exec, node, prev_pipe, NULL);
        if (prev_pipe)
        {
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }
    }
    if (node->type == TYPE_PIPE && node->left) // pensado para casos cat < outfile.txt + multiplos pipes
        handle_pipes(hash, vtr, node, prev_pipe);
    else
        pipe_from_redirect(hash, vtr, node->right, prev_pipe);
}





void handle_pipes(t_hashtable *hash, t_vector *vtr, t_ast *node, int *prev_pipe)
{
    int next_pipe[2];

    if (node == NULL)
        return ;

    if (node->type == TYPE_PIPE)
    {
        pipe(next_pipe);
        execute_pipes(hash, &vtr->exec, node->left, prev_pipe, next_pipe);
        prev_pipe[0] = next_pipe[0];
        prev_pipe[1] = next_pipe[1];
        handle_pipes(hash, vtr, node->right, prev_pipe);
    }
    else if (node->right == NULL && node->type == TYPE_COMMAND)
    {
        execute_pipes(hash, &vtr->exec, node, prev_pipe, NULL);
        if (prev_pipe)
        {
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }
    }
    else if (node->type == TYPE_REDIRECT)
    {
        handle_redirects(vtr, hash, node);
        redirect_execution(vtr, hash, node, prev_pipe);
    }
    else if (node->type == TYPE_LOGICAL)
        handle_logical(vtr, hash, node, prev_pipe);
}





void    execute_pipes(t_hashtable *hashtable, t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
{
    node->pid = fork();
    if (node->pid == 0)
    {
        if (*prev_pipe != -1)
        {
            dup2(prev_pipe[0], STDIN_FILENO);
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }
        if (next_pipe && exec->count_pipes >= 1)
        {
            dup2(next_pipe[1], STDOUT_FILENO);
            close(next_pipe[0]);
            close(next_pipe[1]);
        }
        execute_forked_command(hashtable, node);
        exit(EXIT_SUCCESS);
    }
    else
    {
        wait (NULL);
        if (prev_pipe && !next_pipe)
            close(prev_pipe[1]);

        if (next_pipe && exec->count_pipes >= 1)
            close(next_pipe[1]);
    }
}
