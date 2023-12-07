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

void    generic_exec_cmd(t_hashtable *hashtable, t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe);
void     execute_forked_command(t_hashtable *hashtable, t_ast *node);
int status;




void	exec_multi_cmds(t_vector *vtr, t_hashtable *hashtable, t_ast *root)
{
    int initial_pipe[2] = {-1, -1};
    if (root == NULL)
        return ;

    if (root->type == TYPE_COMMAND)
        execute_forked_command(hashtable, root);

    if (root->type == TYPE_REDIRECT && root->weight != OP_HEREDOC)
        handle_redirects(vtr, hashtable, root);

    if (root->type == TYPE_REDIRECT && root->weight == OP_HEREDOC)
        handle_heredoc(root, hashtable, root->delim);

    else if (root->type == TYPE_OPERATOR && is_logical(node->cmds))
         // operator_execution()

    else if (root->type == TYPE_OPERATOR && root->weight == OP_PIPE)
    {
        handle_pipes(hashtable, vtr, root, initial_pipe);
		restore_fd(vtr->exec.old_stdin, vtr->exec.old_stdout);
	    // wait_for_children(root);
    }
}

void    wait_for_children(t_ast *root)
{
    int status;

    status = 0;
    if (root == NULL)
        return ;

    if (root->type == TYPE_COMMAND)
    {
        waitpid(root->pid, &status, 0);
        if (WIFEXITED(status))
            root->exit_status = WEXITSTATUS(status);
    }
    else if (root->type == TYPE_OPERATOR || root->type == TYPE_REDIRECT)
    {
        wait_for_children(root->left);
        wait_for_children(root->right);
    }
}






void    generic_exec_cmd(t_hashtable *hashtable, t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
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
        wait (&status);
        if (prev_pipe && !next_pipe)
            close(prev_pipe[1]);

        if (next_pipe && exec->count_pipes >= 1)
            close(next_pipe[1]);
    }
}

void execute_forked_command(t_hashtable *hashtable, t_ast *node)
{
	char *path;
	int result;

	result = verify_cmd_permissions(node->cmds);
	if (ft_strchr(node->cmds, '/') != NULL && result != 0) // tratamento para caminho absoluto'
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
    // ft_fprintf(2, "node->path: %s\n", node->path);
	// if (!execute_if_builtin(hashtable, node))
    execve(node->path, node->args, NULL);
	ft_fprintf(2, "minishell: %s: %s\n", node->path, strerror(errno));
	exit(EXIT_FAILURE);
}
