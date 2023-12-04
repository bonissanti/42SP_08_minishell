/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/01 18:54:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"
#include "../include/segments.h"

static void handle_pipes(t_hashtable *hashtable, t_exec *exec, t_ast *node);
void    generic_exec_cmd(t_hashtable *hashtable, t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe);
// void    first_cmd(t_hashtable *hashtable, t_ast *node, int *pipefd);
// void    third_cmd(t_hashtable *hashtable, t_ast *node, int *otario, int *fucker);
// void    fourth_cmd(t_hashtable *hashtable, t_ast *node, int *fucker, int *sucker);
// void second_cmd(t_hashtable *hashtable, t_ast *node, int *pipefd, int *otario);
// void	middle_cmd(t_hashtable *hashtable, t_ast *node, int *pipefd, int *new_pipefd);
// void	final_cmd(t_hashtable *hashtable, t_ast *node, int *pipefd);
static void    wait_for_children(t_ast *root);
static void     execute_forked_command(t_hashtable *hashtable, t_ast *node);




void	exec_multi_cmds(t_vector *vtr, t_hashtable *hashtable, t_ast *root, t_exec *exec)
{

    handle_redirects(vtr, hashtable, root);
	handle_pipes(hashtable, exec, root);
	wait_for_children(root);
    // chama o node->left
    //chama o node->right
    
}

static void    wait_for_children(t_ast *root)
{
    int status;

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


// first_cmd(hashtable, node->left, pipefd);
// second_cmd(hashtable, node->right->left, pipefd, otario);
// third_cmd(hashtable, node->right->right->left, otario, fucker);
// fourth_cmd(hashtable, node->right->right->right, fucker, sucker);

static void handle_pipes(t_hashtable *hashtable, t_exec *exec, t_ast *node)
{
    int next_pipe[2];
    int prev_pipe[2];

    if (node == NULL)
        return ;

    if (node->type == TYPE_OPERATOR)
    {
        generic_exec_cmd(hashtable, exec, node->left, NULL, next_pipe);

        // reciclagem de pipes aqui
        prev_pipe[0] = next_pipe[0];
        prev_pipe[1] = next_pipe[1];
        exec->count_pipes--;

        while (exec->count_pipes > 0)
        {
            pipe(next_pipe);
            if (exec->count_pipes % 2 == 0)
                generic_exec_cmd(hashtable, exec, node->right->left, prev_pipe, next_pipe);
            else
                generic_exec_cmd(hashtable, exec, node->right->right, prev_pipe, next_pipe);
            prev_pipe[0] = next_pipe[0];
            prev_pipe[1] = next_pipe[1];
            exec->count_pipes--;
        }

        // generic_exec_cmd(hashtable, exec, node->right->left, prev_pipe, next_pipe);

        // // segunda reciclagem de pipes aqui


        // generic_exec_cmd(hashtable, exec, node->right->right, prev_pipe, next_pipe);
        if (exec->count_pipes == 0)
            generic_exec_cmd(hashtable, exec, node->right->right, prev_pipe, NULL);
    }
}


void    generic_exec_cmd(t_hashtable *hashtable, t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
{
    if (exec->count_pipes >= 1)
        pipe(next_pipe);
    node->pid = fork();
    if (node->pid == 0)
    {
        if (prev_pipe)
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
        wait (NULL);
        if (prev_pipe && !next_pipe)
            close(prev_pipe[1]);

        if (next_pipe && exec->count_pipes >= 1)
            close(next_pipe[1]);
    }
}


// void    first_cmd(t_hashtable *hashtable, t_ast *node, int *pipefd)
// {
//     pipe(pipefd);
//     node->pid = fork();
//     if (node->pid == 0)
//     {
//         dup2(pipefd[1], STDOUT_FILENO);
//         close(pipefd[1]);
//         close(pipefd[0]);
// 		// execute_forked_command(hashtable, node); não executa mais aqui
// 		// exit(EXIT_SUCCESS);
//     }
// 	else
//         wait(NULL);
// 		close(pipefd[1]);
// }

// void second_cmd(t_hashtable *hashtable, t_ast *node, int *pipefd, int *otario)
// {

//     pipe(otario);
//     node->pid = fork();
//     if (node->pid == 0)
//     {
//         // le do pipe anterior
//         dup2(pipefd[0], STDIN_FILENO);
//         // ft_printf_fd(pipefd[0]);
//         close(pipefd[0]);
//         close(pipefd[1]);

//         // escreve no pipe atual
//         dup2(otario[1], STDOUT_FILENO);
//         close(otario[0]);
//         close(otario[1]);
//         execute_forked_command(hashtable, node);
//         exit(EXIT_SUCCESS);
//     }
//     else
//     {
//         close(otario[1]);
//         // close(pipefd[1]); // hang/erro por fechar a escrita do pipe anterior
//     }
// }

// void    third_cmd(t_hashtable *hashtable, t_ast *node, int *otario, int *fucker)
// {
//     pipe(fucker);
//     node->pid = fork();
//     if (node->pid == 0)
//     {
//         //le do pipe anterior
//         dup2(otario[0], STDIN_FILENO);
//         close(otario[0]);
//         close(otario[1]);

//         //escreve no pipe atual
//         dup2(fucker[1], STDOUT_FILENO);
//         close(fucker[0]);
//         close(fucker[1]);
//         execute_forked_command(hashtable, node);
//         exit(EXIT_SUCCESS);
//     }
//     else
//         close(fucker[1]);
// }

// void    fourth_cmd(t_hashtable *hashtable, t_ast *node, int *fucker, int *sucker)
// {
//     pipe(sucker);
//     node->pid = fork();
//     if (node->pid == 0)
//     {
//         dup2(fucker[0], STDIN_FILENO);
//         close(fucker[0]);
//         close(fucker[1]);

//         dup2(sucker[1], STDOUT_FILENO);
//         close(sucker[0]);
//         close(sucker[1]);
//         execute_forked_command(hashtable, node);
//         exit(EXIT_SUCCESS);
//     }
//     else
//         close(sucker[1]);
// }



static void execute_forked_command(t_hashtable *hashtable, t_ast *node)
{
	char *path;
	int result;

	result = verify_cmd_permissions(node->cmds);
	if (ft_strchr(node->cmds, '/') != NULL && result == 0) // tratamento para caminho absoluto'
	{
		if (result == 126) // tacar isso numa função para printar erro de permissão
			ft_fprintf(2, "minishell: %s: command not found\n", node->cmds);
		else if (result == 127)
			ft_fprintf(2, "minishell: %s: %s\n", node->cmds, strerror(errno));
		return ;
	}
	else
	{
		path = search(hashtable, "PATH")->value;
		node->path = build_cmd_path(node, path);
	}
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
