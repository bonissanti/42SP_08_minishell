/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 20:02:47 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_multi_cmds(t_exec *exec, t_hashtable *hashtable, t_ast *root)
{
	int	initial_pipe[2];
	t_ast *heredoc_node;
	t_bool heredoc_executed;

	initial_pipe[0] = -1;
	initial_pipe[1] = -1;
	heredoc_executed = false;
	if (root == NULL)
		return (0);

	if (root->type != TYPE_HEREDOC)
	{
		heredoc_node = find_heredoc(root);
		if (heredoc_node && !heredoc_executed)
		{
			analyze_heredoc(exec, heredoc_node, hashtable);
			heredoc_executed = true;
		}
	}
	if (root->type == TYPE_COMMAND)
		exec_forked_cmd(hashtable, root);
	if (root->type == TYPE_REDIRECT)
	{
		handle_redirects(root);
		analyze_redirect(exec, hashtable, root);
	}
	if (root->type == TYPE_HEREDOC)
		analyze_heredoc(exec, root, hashtable);
	if (root->type == TYPE_PIPE)
	{
		handle_pipes(hashtable, exec, root, initial_pipe);
		restore_fd(exec->old_stdin, exec->old_stdout);
	}
	if (root->type == TYPE_LOGICAL)
	{
		handle_logical(exec, hashtable, root);
		restore_fd(exec->old_stdin, exec->old_stdout);
	}
	return (g_global.exit_status);
}

void    wait_for_children(t_ast *node)
{
    int status;

    status = 0;
    if (node == NULL)
        return ;

    if (node->type == TYPE_REDIRECT || node->type == TYPE_COMMAND || node->type == TYPE_PIPE ||  node->type == TYPE_HEREDOC
		|| node->type == TYPE_LOGICAL)
    {
        waitpid(node->pid, &status, 0);
        if (WIFEXITED(status))
            g_global.cmd_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_global.cmd_status = WTERMSIG(status);
    }
    else if (node->right)
        wait_for_children(node->right);
}

int	exec_forked_cmd(t_hashtable *hash, t_ast *node)
{
	if (!analyze_cmd(hash, node))
		return (g_global.cmd_status);
	if (is_builtin(node))
		execute_builtin(hash, node);
	else
		g_global.cmd_status = forking(node);
	
	return (g_global.exit_status);
}

int	forking(t_ast *node)
{
	node->pid = fork();
	if (node->type == TYPE_COMMAND)
	{
		if (node->pid == 0)
		{
			g_global.cmd_status = execve(node->path, node->args, NULL);
			exit(g_global.cmd_status);
		}
	}
	return (g_global.cmd_status);
}