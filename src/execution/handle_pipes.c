/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:40:02 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/04 19:09:22 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: Handle_other
 * -----------------
 * This function is used to handle the other cases of the handle_pipes, as
 * the logical operators. It calls the function execute_pipes to execute the
 * command, then it calls the function simple_logical to wait for the children
 * and execute the next command if the status of the command is 0.
 *
 * @param: hash: The pointer to the hashtable.
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: prev_pipe: The pointer to the pipe that is going to be read.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

void	handle_other(t_exec *exec, t_hashtable *hash, t_ast *node,
		int *prev_pipe)
{
	if (node->type == TYPE_LOGICAL)
	{
		execute_pipes(exec, node->left, prev_pipe, NULL);
		simple_logical(exec, hash, node, node->left->num_status);
	}
	else
	{
		restore_fd(exec->old_stdin, exec->old_stdout);
		exec_multi_cmds(exec, hash, node);
	}
}

/**
 * Function: Final_cmd
 * -----------------
 * This function is used to handle the other cases of the handle_pipes, as
 * the logical operators. It calls the function execute_pipes to execute the
 * command, then it calls the function simple_logical to wait for the children
 * and execute the next command if the status of the command is 0.
 *
 * @param: hash: The pointer to the hashtable.
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: prev_pipe: The pointer to the pipe that is going to be read.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

static void	final_cmd(t_exec *exec, t_ast *node, int *prev_pipe)
{
	execute_pipes(exec, node, prev_pipe, NULL);
	if (prev_pipe)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
}

/**
 * Function: Last_pipe
 * -----------------
 * This function is the final process of handle_pipes. It executes the last
 * command of the pipe, and closes the pipe. It could works in the 2 ways.
 * The first if is for the case of a final command in the multiples pipes or
 * for the last command after a redirection/heredoc. The second if is for the
 * The case of redirection/heredoc in the middle of the pipes. This if is
 * for to garantee that the command is executed and, if has multiples pipes,
 * could follow the flow of the pipes.
 *  
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: node: The pointer to the node that contains the redirection.
 * @param: prev_pipe: The pointer to the pipe that is going to be read.
 * 
 * @var: exec->error_call: The boolean that indicates if the command has an
 * error. It is setted to false or true by the function handle_redirect in
 * create_files.
 * @var: exec->count_pipes: The number of pipes that the command has.
 * @var: exec->read_in: The boolean that indicates if the command must
 * read from the input file instead of the pipe. This flag is exclusive
 * for this function, thinking for the case of pipes + redirect + pipe/multiple
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

static void	last_pipe(t_exec *exec, t_ast *node, int *prev_pipe)
{
	int	next_pipe[2];

	if (exec->count_pipes == 0 || (exec->error_call == 1
			&& exec->count_pipes >= 1))
		final_cmd(exec, node, prev_pipe);
	else if (exec->count_pipes >= 1)
	{
		pipe(next_pipe);
		if (node->cmds && *node->cmds == '<')
			exec->read_in = true;
		execute_pipes(exec, node, prev_pipe, next_pipe);
		prev_pipe[0] = next_pipe[0];
		prev_pipe[1] = next_pipe[1];
		exec->read_in = false;
		if (node->right)
			node = node->right;
		handle_pipes(g_global.hash, exec, node->right, prev_pipe);
		if (prev_pipe)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
	}
}

/**
 * Function: handle_pipes
 * -----------------
 * This function is the heart of the pipes. It handles the pipes, basically.
 * It calls the node->left to execute the first command, then it passes the
 * content of the pipe (next_pipe) to the int prev_pipe, so that the next
 * command can read from it. The logical of handle_pipes is recursive and
 * recycling the pipes. In some cases, the next node could be a redirection,
 * a pipe or a logical operator, so it calls the functions handle_redirect.
 *  
 * @param: hash: The pointer to the hashtable.
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: node: The pointer to the node that contains the redirection.
 * @param: prev_pipe: The pointer to the pipe that is going to be read.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

void	handle_pipes(t_hashtable *hash, t_exec *exec, t_ast *node,
		int *prev_pipe)
{
	int	next_pipe[2];

	if (node == NULL)
		return ;
	if (node->right && *node->right->cmds == '>')
		exec->has_out = true;
	if (node->type == TYPE_PIPE)
	{
		pipe(next_pipe);
		if (node->left)
			execute_pipes(exec, node->left, prev_pipe, next_pipe);
		exec->has_out = false;
		prev_pipe[0] = next_pipe[0];
		prev_pipe[1] = next_pipe[1];
		if (node->right)
			handle_pipes(hash, exec, node->right, prev_pipe);
	}
	else if ((node->right == NULL && node->type != TYPE_HEREDOC)
		|| (node->type == TYPE_COMMAND || node->type == TYPE_REDIRECT))
		last_pipe(exec, node, prev_pipe);
	else if (node->type != TYPE_PIPE && node->type != TYPE_REDIRECT
		&& node->type != TYPE_HEREDOC)
		handle_other(exec, hash, node, prev_pipe);
	close_all_fds();
}
