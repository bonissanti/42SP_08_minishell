/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:40:02 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/21 11:50:54 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_other(t_exec *exec, t_hashtable *hash, t_ast *node,
		int *prev_pipe)
{
	if (node->type == TYPE_LOGICAL)
	{
		execute_pipes(exec, node->left, prev_pipe, NULL);
		simple_logical(exec, hash, node, node->left->num_status);
	}
	else
	{
		restore_fd(exec->old_stdin, exec->old_stdout);
		exec_multi_cmds(exec, hash, node);
	}
}

static void	last_pipe(t_exec *exec, t_ast *node, int *prev_pipe)
{
	signal(SIGPIPE, SIG_IGN);
	execute_pipes(exec, node, prev_pipe, NULL);
}

void handle_pipes(t_hashtable *hash, t_exec *exec, t_ast *node, int *prev_pipe)
{
    int next_pipe[2];
    t_ast *current_node = node;

    while (current_node != NULL) 
	{
        if (current_node->type == TYPE_PIPE) 
		{
            pipe(next_pipe);
            if (current_node->left)
                execute_pipes(exec, current_node->left, prev_pipe, next_pipe);
            prev_pipe[0] = next_pipe[0];
            prev_pipe[1] = next_pipe[1];
            exec->count_pipes--;
        } 
		else if (current_node->right == NULL && (current_node->type == TYPE_COMMAND || current_node->type == TYPE_REDIRECT))
            last_pipe(exec, current_node, prev_pipe);
		else if (current_node->type != TYPE_PIPE && current_node->type != TYPE_REDIRECT && current_node->type != TYPE_HEREDOC)
            handle_other(exec, hash, current_node, prev_pipe);
        current_node = current_node->right;
    }
	fechar_todos_fds();
}


