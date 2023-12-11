/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/11 19:08:25 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/segments.h"

static void    wait_for_children(t_ast *node);

void	exec_multi_cmds(t_vector *vtr, t_hashtable *hashtable, t_ast *root)
{
	int	initial_pipe[2];

	initial_pipe[0] = -1;
	initial_pipe[1] = -1;
	if (root == NULL)
		return ;
	if (root->type == TYPE_COMMAND)
		execute_command(vtr, hashtable, root);
	if (root->type == TYPE_REDIRECT && root->weight != OP_HEREDOC)
	{
		handle_redirects(vtr, root);
		redirect_execution(vtr, hashtable, root, initial_pipe);
	}
	if (root->type == TYPE_REDIRECT && root->weight == OP_HEREDOC)
		handle_heredoc(vtr, root, hashtable, root->delim);
	if (root->type == TYPE_PIPE)
	{
		handle_pipes(hashtable, vtr, root, initial_pipe);
		restore_fd(vtr->exec.old_stdin, vtr->exec.old_stdout);
	}
	if (root->type == TYPE_LOGICAL)
		logical_pipe(vtr, hashtable, root, initial_pipe);
	wait_for_children(root);
}

static void    wait_for_children(t_ast *node)
{
    int status;

    status = 0;
    if (node == NULL)
        return ;

    if (node->type == TYPE_COMMAND)
    {
        waitpid(node->pid, &status, 0);
        if (WIFEXITED(status))
            node->num_status = WEXITSTATUS(status);
    }
    else if (node->type == TYPE_PIPE || node->type == TYPE_REDIRECT)
    {
        wait_for_children(node->left);
        wait_for_children(node->right);
    }
}

void	execute_command(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	char	*path;
	int		result;

	result = verify_cmd_permissions(node->cmds);
	if (result != 0)
	{
		handle_error(node, result);
		return ;
	}
	else if (ft_strchr(node->cmds, '/') != NULL && result == 0)
		node->path = ft_strdup(node->cmds);
	else
	{
		path = search(hashtable, "PATH")->value;
		node->path = build_cmd_path(node, path);
	}
	if (!execute_if_builtin(vtr, hashtable, node))
		execve(node->path, node->args, NULL);
}
