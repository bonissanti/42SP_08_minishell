/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/06 20:18:05 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"
#include "../include/segments.h"

t_global g_global;

static void handle_pipes(t_vector *vtr, t_hashtable *hashtable, t_exec *exec, t_ast *node, int *prev_pipe);
void    generic_exec_cmd(t_vector *vtr, t_hashtable *hashtable, t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe);
static void    wait_for_children(t_ast *root);
void	execute_forked_command(t_vector *vtr, t_hashtable *hashtable, t_ast *node);
void	execute_and_or(t_vector  *vtr, t_hashtable *hashtable, t_ast *node, int *prev_pipe, t_exec *exec);

void	exec_multi_cmds(t_vector *vtr, t_hashtable *hashtable, t_ast *root, t_exec *exec)
{
    int initial_pipe[2] = {-1, -1};
    
    if (root == NULL)
        return ;
    if (root->type == TYPE_REDIRECT)
        handle_redirects(vtr, hashtable, root, exec);
    else if (root->type == TYPE_OPERATOR && is_logical(root->cmds))
		execute_and_or(vtr, hashtable, root, initial_pipe, exec);
    else if (root->type == TYPE_OPERATOR && *root->cmds == '|')
    {
        handle_pipes(vtr, hashtable, exec, root, initial_pipe);
	    wait_for_children(root);
    }
	else if(root->type == TYPE_COMMAND)
		execute_forked_command(vtr, hashtable, root);
}

static void    wait_for_children(t_ast *root)
{
    int status = 0;

    if (root == NULL)
        return ;

    if (root->type == TYPE_COMMAND)
    {
        waitpid(root->pid, &status, 0);
        if (WIFEXITED(status))
            g_global.exit_status = WEXITSTATUS(status);
    }
    else if (root->type == TYPE_OPERATOR || root->type == TYPE_REDIRECT)
    {
        wait_for_children(root->left);
        wait_for_children(root->right);
    }
}


static void handle_pipes(t_vector *vtr, t_hashtable *hash, t_exec *exec, t_ast *node, int *prev_pipe)
{
    int next_pipe[2];

    if (node == NULL)
        return ;

    if (node->type == TYPE_OPERATOR && ft_strncmp(node->cmds, "||", 2) && *node->cmds == '|') // this condition may cause a problem "node->weight == OP_PIPE"
    {
        pipe(next_pipe);
        generic_exec_cmd(vtr, hash, exec, node->left, prev_pipe, next_pipe);
        prev_pipe[0] = next_pipe[0];
        prev_pipe[1] = next_pipe[1];
        handle_pipes(vtr, hash, exec, node->right, prev_pipe);
    }
    else if (node->right == NULL && node->type == TYPE_COMMAND) // so it can print in the stdout if t is the last node
        generic_exec_cmd(vtr, hash, exec, node, prev_pipe, NULL);
	else if (is_logical(node->cmds))
		execute_and_or(vtr, hash, node, prev_pipe, exec);
	else if (node->type == TYPE_REDIRECT)
	{
		handle_redirects(vtr, hash, node, exec);
		dup2(node->fd, STDOUT_FILENO);
		close(node->fd);
		generic_exec_cmd(vtr, hash, exec, node->left, prev_pipe, NULL);
		exec_multi_cmds(vtr, hash, node, exec); // MAY SEGFAULT!!
	}
	else
	{
		ft_printf("node: %s\n", node->cmds);
		exec_multi_cmds(vtr, hash, node, exec);
	}
}


void    generic_exec_cmd(t_vector *vtr, t_hashtable *hashtable, t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
{
    // if (exec->count_pipes >= 1)
    //     pipe(next_pipe);
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
		else if(exec->out_fd != 0)
		{
			dup2(exec->out_fd, STDOUT_FILENO);
			close(exec->out_fd);
		}
        execute_forked_command(vtr, hashtable, node); // better if its a int?
        exit(EXIT_SUCCESS);
    }
    else
    {
        wait_for_children(node);
        if (prev_pipe && !next_pipe)
            close(prev_pipe[1]);

        if (next_pipe && exec->count_pipes >= 1)
            close(next_pipe[1]);
        
    }
}

void execute_forked_command(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
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
    ft_fprintf(2, "node->path: %s\n", node->path);
	if(!execute_if_builtin(vtr, hashtable, node))
	{			
		execve(node->path, node->args, NULL);
		ft_fprintf(2, "minishell: %s: %s\n", node->path, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	execute_and_or(t_vector  *vtr, t_hashtable *hashtable, t_ast *node, int *prev_pipe, t_exec *exec)
{
	generic_exec_cmd(vtr, hashtable, exec, node->left, prev_pipe, NULL);
	if ((!ft_strncmp(node->cmds, "&&", 2) && g_global.exit_status == 0)
	|| (!ft_strncmp(node->cmds, "||", 2) && g_global.exit_status != 0))
		exec_multi_cmds(vtr, hashtable, node->right, exec);
}
