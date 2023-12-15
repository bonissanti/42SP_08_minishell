/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 13:25:27 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void    wait_for_children(t_ast *node);

int	exec_multi_cmds(t_exec *exec, t_hashtable *hashtable, t_ast *root)
{
	int	initial_pipe[2];

	initial_pipe[0] = -1;
	initial_pipe[1] = -1;
	if (root == NULL)
		return (0);
	if (root->type == TYPE_COMMAND)
		execute_command(hashtable, root);
	if (root->type == TYPE_REDIRECT)
	{
		handle_redirects(root);
		analyze_redirect(exec, hashtable, root);
	}
	if (root->type == TYPE_HEREDOC)
		analyze_heredoc(exec, root, hashtable, root->delim);
	if (root->type == TYPE_PIPE)
	{
		handle_pipes(hashtable, exec, root, initial_pipe);
		restore_fd(exec->old_stdin, exec->old_stdout);
	}
	if (root->type == TYPE_LOGICAL)
		logical_pipe(exec, hashtable, root, initial_pipe);
	wait_for_children(root);
	return (g_global.exit_status);
}

static void    wait_for_children(t_ast *node)
{
    int status;

    status = 0;
    if (node == NULL)
        return ;

    if (node->type == TYPE_COMMAND || node->type == TYPE_PIPE || node->type == TYPE_REDIRECT || node->type == TYPE_HEREDOC)
    {
        waitpid(node->pid, &status, 0);
        if (WIFEXITED(status))
            node->num_status = WEXITSTATUS(status);
		if (node->num_status == 1)
			g_global.exit_status = 1;
    }
    else if (node->right)
        wait_for_children(node->right);
}

int	execute_command(t_hashtable *hashtable, t_ast *node)
{
	analyze_cmd(hashtable, node);
	if (is_builtin(node))
		g_global.exit_status = execute_builtin(hashtable, node);
	else
		g_global.exit_status = forking(node, hashtable);
	return (g_global.exit_status);
}

int	forking(t_ast *node, t_hashtable *hashtable)
{
	node->pid = fork();
	if (node->type == TYPE_COMMAND)
	{
		if (node->pid == 0)
		{
			g_global.exit_status = execve(node->path, node->args, NULL);
			exit(g_global.exit_status);
		}
		else
			waitpid(node->pid, &node->num_status, 0);
	}
	return (g_global.exit_status);
}