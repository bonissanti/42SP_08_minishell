/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/05 20:23:55 by aperis-p         ###   ########.fr       */
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
void	execute_and_or(t_vector  *vtr, t_hashtable *hashtable, t_ast *node, t_exec *exec);

void	exec_multi_cmds(t_vector *vtr, t_hashtable *hashtable, t_ast *root, t_exec *exec)
{
    int initial_pipe[2] = {-1, -1};
	int status = 0;
    
    if (root == NULL)
        return ;
    if (root->type == TYPE_REDIRECT)
        handle_redirects(vtr, hashtable, root, exec);
    else if (root->type == TYPE_OPERATOR
    && (!ft_strncmp(root->cmds, "&&", 2)
    || !ft_strncmp(root->cmds, "||", 2)))
    {
		if ((ft_strncmp(root->cmds, "&&", 2) == 0 && WEXITSTATUS(status) == 0)
		|| (ft_strncmp(root->cmds, "||", 2) == 0 && WEXITSTATUS(status) != 0))
        	exec_multi_cmds(vtr, hashtable, root->right, exec);
		else
			return ;
			// execute_and_or(vtr, hashtable, root, exec);
	    // wait_for_children(root);
    }
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
    else if (node->right == NULL)
        generic_exec_cmd(vtr, hash, exec, node, prev_pipe, NULL);
	else
		exec_multi_cmds(vtr, hash, node, exec);
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
        execute_forked_command(vtr, hashtable, node); // better if its a int?
        exit(EXIT_SUCCESS);   
    }
    else
    {
        wait (NULL);
        if (prev_pipe && !next_pipe)
            close(prev_pipe[1]);

        if (next_pipe && exec->count_pipes >= 1)
            close(next_pipe[1]);
        
    }
}

void    handle_error(t_ast *node, int result)
{
    if (result == 126)
        ft_fprintf(2, "minishell: %s: command not found\n", node->cmds);
    else if (result == 127)
        ft_fprintf(2, "minishell: %s: %s\n", node->cmds, strerror(errno));
    return ;
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
	execute_if_builtin(vtr, hashtable, node);
    // execve(node->path, node->args, NULL);
    // ft_fprintf(2, "minishell: %s: %s\n", node->path, strerror(errno));
    // exit(EXIT_FAILURE);
}

t_ast *branch_tip(t_ast *node)
{
	t_ast *first;

	if(!node)
		return (NULL);
	first = node;
	if(first->left == NULL)
		return (first);
	else
	{
		while(first->left)
			first = first->left;
	}
	return(first);
}

void	execute_and_or(t_vector  *vtr, t_hashtable *hashtable, t_ast *node, t_exec *exec)
{
	int status;
	pid_t pid;
	
	pid = fork();
	if (pid == -1)
	{
		ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
		return ;
	}
	if (pid == 0)
	{
		if (!execute_if_builtin(vtr, hashtable, branch_tip(node->left)))
			exit(execve(branch_tip(node->left)->path, branch_tip(node->left)->args, NULL));
	}
	else
	{
		waitpid(pid, &status, 0);
		if ((ft_strncmp(node->cmds, "&&", 2) == 0 && WEXITSTATUS(status) == 0)
			|| (ft_strncmp(node->cmds, "||", 2) == 0 && WEXITSTATUS(status) != 0))
            exec_multi_cmds(vtr, hashtable, node->right, exec);
	}
}


// static void    handle_pipes(t_hashtable *hashtable, t_ast *root, t_exec *exec)
// {
//     int pipefd[2];

//     if (root == NULL)
//         return ;

//     if (root->type == TYPE_OPERATOR && root->weight == OP_PIPE)
//     {
//         pipe(pipefd);
//         backup_fd(&exec->old_stdin, &exec->old_stdout);
//         swap_fd(pipefd[1], STDOUT_FILENO);
//         assign_and_exec_pids(hashtable, root->left);
//         restore_fd(exec->old_stdin, exec->old_stdout);
//         swap_fd(pipefd[0], STDIN_FILENO);
//         assign_and_exec_pids(hashtable, root->right);
//         restore_fd(exec->old_stdin, exec->old_stdout);
        
//     }
//     else 
//     {
//         handle_pipes(hashtable, root->left, exec);
//         handle_pipes(hashtable, root->right, exec);
//     }
// }
