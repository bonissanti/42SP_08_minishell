/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/11 14:43:47 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void     execute_forked_command(t_hashtable *hashtable, t_ast *node);


void	exec_multi_cmds(t_vector *vtr, t_hashtable *hashtable, t_ast *root)
{
    int initial_pipe[2] = {-1, -1};
    if (root == NULL)
        return ;

    if (root->type == TYPE_COMMAND)
        execute_forked_command(hashtable, root);

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
}

void execute_forked_command(t_hashtable *hashtable, t_ast *node)
{
	char *path;
	int result;

	result = verify_cmd_permissions(node->cmds);
	if (ft_strchr(node->cmds, '/') != NULL && result != 0)
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
    execve(node->path, node->args, NULL);
	ft_fprintf(2, "minishell: %s: %s\n", node->path, strerror(errno));
	exit(EXIT_FAILURE);
}
