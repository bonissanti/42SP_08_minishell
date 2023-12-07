/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 18:36:21 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"
#include "../include/segments.h"

static void handle_pipes(t_hashtable *hash, t_vector *vtr, t_ast *node, int *prev_pipe);
void    generic_exec_cmd(t_hashtable *hashtable, t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe);
// static void    wait_for_children(t_ast *root);
void     execute_forked_command(t_hashtable *hashtable, t_ast *node);




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

    else if (root->type == TYPE_OPERATOR && root->weight == OP_PIPE)
    {
        handle_pipes(hashtable, vtr, root, initial_pipe);
		restore_fd(vtr->exec.old_stdin, vtr->exec.old_stdout);
	    // wait_for_children(root);
    }
}

// static void    wait_for_children(t_ast *root)
// {
//     int status;

//     status = 0;
//     if (root == NULL)
//         return ;

//     if (root->type == TYPE_COMMAND)
//     {
//         waitpid(root->pid, &status, 0);
//         if (WIFEXITED(status))
//             root->exit_status = WEXITSTATUS(status);
//     }
//     else if (root->type == TYPE_OPERATOR || root->type == TYPE_REDIRECT)
//     {
//         wait_for_children(root->left);
//         wait_for_children(root->right);
//     }
// }

static void    redirect_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node, int *prev_pipe)
{
    pid_t pid;

    if (node->type == TYPE_REDIRECT)
    {   
        pid = fork();
        if (prev_pipe)
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
            execute_forked_command(hashtable, node->left);
        else
        {
            wait(NULL);
            close(prev_pipe[1]);
        }
    }
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
        // if (!next_pipe && exec->out_fd != 0)
        // {
        //     dup2(exec->out_fd, STDOUT_FILENO);
        //     close(exec->out_fd);
        // }
        execute_forked_command(hashtable, node);
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
