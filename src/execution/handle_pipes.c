/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:40:02 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 19:07:15 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"

int is_logical(char *operator)
{
    if(!ft_strncmp(operator, "&&", 2) || !ft_strncmp(operator, "||", 2))
        return (true);
    return(false);
}

static void handle_pipes(t_hashtable *hash, t_vector *vtr, t_ast *node, int *prev_pipe)
{
    int next_pipe[2];

    if (node == NULL)
        return ;

    if (node->type == TYPE_OPERATOR && node->weight == OP_PIPE)
    {
        pipe(next_pipe);
        generic_exec_cmd(hash, &vtr->exec, node->left, prev_pipe, next_pipe);
        prev_pipe[0] = next_pipe[0];
        prev_pipe[1] = next_pipe[1];
        handle_pipes(hash, vtr, node->right, prev_pipe);
    }
    else if (node->right == NULL && node->type == TYPE_COMMAND)
    {
        generic_exec_cmd(hash, &vtr->exec, node, prev_pipe, NULL);
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

	else if (node->type == TYPE_OPERATOR && is_logical(node->cmds))
	{
		generic_exec_cmd(hash, &vtr->exec, node->left, prev_pipe, NULL);
		if ((!ft_strncmp(node->cmds, "&&", 2) && status == 0)
    		|| (!ft_strncmp(node->cmds, "||", 2) && status != 0))
			exec_multi_cmds(vtr, hash, node->right);
	}
}