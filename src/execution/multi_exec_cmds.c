/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 19:17:49 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"
#include "../include/segments.h"

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
        handle_redirects(vtr, hashtable, root);
        redirect_execution(vtr, hashtable, root, initial_pipe);
    }

    // if (root->type == TYPE_REDIRECT && root->weight == OP_HEREDOC)
    //     handle_heredoc(root, hashtable, root->delim);

    if (root->type == TYPE_PIPE)
    {
        pipe_from_redirect(hashtable, vtr, root, initial_pipe);
        // handle_pipes(hashtable, vtr, root, initial_pipe);
		restore_fd(vtr->exec.old_stdin, vtr->exec.old_stdout);
    }

    if (root->type == TYPE_LOGICAL)
        handle_logical(vtr, hashtable, root, initial_pipe);
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
