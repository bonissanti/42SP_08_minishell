/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:43:27 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 19:11:40 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/segments.h"

void	handle_redirects(t_vector *vtr, t_ast *node)
{
	t_redirect	*current;

	current = vtr->redirect;
	while (current->name)
	{
		if (ft_strcmp(current->name, node->cmds) == 0)
		{
			current->function(node, node->delim);
			break ;
		}
		current++;
	}
}

void    redirect_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node, int *prev_pipe)
{
    int next_pipe[2];
    pid_t pid;

    if (vtr->exec.count_pipes >= 1)
        pipe(next_pipe);

    if (node->type == TYPE_REDIRECT)
    {   
        pid = fork();
        if (*prev_pipe != -1)
        {
            dup2(prev_pipe[0], STDIN_FILENO);
            close(prev_pipe[0]);
        }
        if (node->in_fd != -1)
        {
            dup2(node->in_fd, STDIN_FILENO);
            close(node->in_fd);
        }
        if (node->out_fd != -1)
        {
            dup2(node->out_fd, STDOUT_FILENO);
            close(node->out_fd);
        }
        if (pid == 0)
        {
            if (vtr->exec.count_pipes >= 1)
            {
                dup2(next_pipe[1], STDOUT_FILENO);
                close(next_pipe[1]);
                execute_forked_command(hashtable, node->left);
                exit(0);
            }
            else
                execute_forked_command(hashtable, node->left); 
        }
        else
        {
            wait(NULL);
            close(prev_pipe[1]);
            if (vtr->exec.count_pipes >= 1)
            {
                close(next_pipe[1]);
                vtr->exec.count_pipes--;
                pipe_from_redirect(hashtable, vtr, node->right, next_pipe);
            }
        }
        if (node->type == TYPE_REDIRECT && node->right->type == TYPE_LOGICAL)
        {
            waitpid(node->pid, &node->left->exit_status, 0);
            simple_logical(vtr, hashtable, node->right, node->left->exit_status);
        }
        
    }
}