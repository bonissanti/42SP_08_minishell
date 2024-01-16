/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:01:50 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/15 20:46:20 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: parent_pipe
 * -----------------
 * Parent process of the execution of a pipe. Basically, it closes the pipes
 * that are not going to be used in the execution and decrements the number
 * of pipes that are going to be used.
 *  
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: prev_pipe: The pointer to the pipe that is going to be read.
 * @param: next_pipe: The pointer to the pipe that is going to be written.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

static void	parent_pipe(t_exec *exec, int *prev_pipe, int *next_pipe)
{
	if (prev_pipe && !next_pipe)
		close(prev_pipe[1]);
	if (next_pipe)
		close(next_pipe[1]);
	exec->count_pipes--;
}

/**
 * Function: redirect_pipes
 * -----------------
 * This function is used to redirect the pipes to the stdin and stdout of the
 * command that is going to be executed. It is used in the child process of
 * the execution of the pipes. When prev_pipe is not -1, it means that the
 * command has a previous pipe, so it redirects the stdin to the pipe. When 
 * next_pipe is not NULL and exec->count_pipes >= 1, it means that the command
 * has a next pipe, so it redirects the stdout to the pipe until the count of
 * pipes is 0.
 * 
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: prev_pipe: The pointer to the pipe that is going to be read.
 * @param: next_pipe: The pointer to the pipe that is going to be written.
 * @var: exec->read_in: The boolean that indicates if the command must
 * read from the input file instead of the pipe. Here, it is used to avoid
 * to redirect the stdin to the pipe when the command has a redirection.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

static void	redirect_pipes(t_exec *exec, int *prev_pipe, int *next_pipe)
{
	if (*prev_pipe != -1 && !exec->read_in)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (next_pipe && exec->count_pipes >= 1)
	{
		dup2(next_pipe[1], STDOUT_FILENO);
		close(next_pipe[1]);
		close(next_pipe[0]);
	}
}

/**
 * Function: child_pipe
 * -----------------
 * This function is used to redirect the pipes to the stdin and stdout of the
 * command that is going to be executed. It is used in the child process of
 * the execution of the pipes. When prev_pipe is not -1, it means that the
 * command has a previous pipe, so it redirects the stdin to the pipe. When 
 * next_pipe is not NULL and exec->count_pipes >= 1, it means that the command
 * has a next pipe, so it redirects the stdout to the pipe until the count of
 * pipes is 0.
 * 
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: prev_pipe: The pointer to the pipe that is going to be read.
 * @param: next_pipe: The pointer to the pipe that is going to be written.
 * @var: exec->read_in: The boolean that indicates if the command must
 * read from the input file instead of the pipe. Here, it is used to avoid
 * to redirect the stdin to the pipe when the command has a redirection.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

void	child_pipe(t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
{
	t_shell	*shell;

	shell = get_shell();
	if (node->type == TYPE_PIPE || node->type == TYPE_COMMAND || exec->has_out
		|| exec->read_in)
		redirect_pipes(exec, prev_pipe, next_pipe);
	else
		close(next_pipe[0]);
	if (node->type == TYPE_REDIRECT && node->to_exec)
	{
		create_files(node, exec, 1);
		if (node->left && node->to_exec)
			node = node->left;
		else
			free_for_finish(exec, shell->hash);
	}
	if (node && node->to_exec)
		exec_simple(shell->hash, exec, node);
	else
		free_for_finish(exec, shell->hash);
	(close_all_fds(), close(0), close(1));
	exit(0);
}

/**
 * Function: execute_pipes
 * -----------------
 * This function is used to redirect the pipes to the stdin and stdout of the
 * command that is going to be executed. It is used in the child process of
 * the execution of the pipes. When prev_pipe is not -1, it means that the
 * command has a previous pipe, so it redirects the stdin to the pipe. When 
 * next_pipe is not NULL and exec->count_pipes >= 1, it means that the command
 * has a next pipe, so it redirects the stdout to the pipe until the count of
 * pipes is 0.
 * 
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: prev_pipe: The pointer to the pipe that is going to be read.
 * @param: next_pipe: The pointer to the pipe that is going to be written.
 * @var: exec->read_in: The boolean that indicates if the command must
 * read from the input file instead of the pipe. Here, it is used to avoid
 * to redirect the stdin to the pipe when the command has a redirection.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

void	execute_pipes(t_exec *exec, t_ast *node, int *prev_pipe, int *next_pipe)
{
	node->pid = fork();
	exec_signals(node->pid);
	if (node->pid == 0)
		child_pipe(exec, node, prev_pipe, next_pipe);
	else
		parent_pipe(exec, prev_pipe, next_pipe);
}
