/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/04 16:54:52 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: Heredoc_first
 * -----------------
 * This function is used to garantee that the heredoc is executed first.
 * If the three conditions are true, we will know that the heredoc is present,
 * than first we count the number of pipes before the heredoc, then we substract
 * the number of pipes to the total of pipes. After that, we find the node of
 * the heredoc and we execute it. 
 * 
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: hash: The pointer to the hashtable.
 * @param: root: The pointer to the root node of the ast.
 * @var: pipes: The number of pipes before the heredoc.
 * @var: heredoc_node: The pointer to the node of the heredoc.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

static t_bool	heredoc_first(t_exec *exec, t_hashtable *hash, t_ast *root)
{
	int		pipes;
	t_ast	*heredoc_node;

	pipes = 0;
	if (root == NULL || (root->type != TYPE_HEREDOC && !root->left && !root->right))
		return (false);
	if (root->type == TYPE_REDIRECT && root->right
		&& root->right->type == TYPE_HEREDOC && !root->left)
		return (false);
	if (exec->count_hdoc == 0)
		return (false);
	pipes = pipe_to_ignore(root, &pipes);
	exec->count_pipes -= pipes;
	heredoc_node = find_node(root, TYPE_HEREDOC);
	if (heredoc_node == NULL)
		return (false);
	else
		g_global.cmd_status = analyze_heredoc(exec, heredoc_node, hash);
	return (true);
}

/**
 * Function: Handle_cmd
 * -----------------
 * This function is the heart of the execution. It is used to handle the
 * different types of nodes of the ast. If the node is a command, it will
 * execute the command. If the node is a redirection, it will execute the
 * redirection. If the node is a pipe, it will execute the pipe. If the node
 * is a logical operator, it will execute the logical operator.
 * 
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: hash: The pointer to the hashtable.
 * @param: root: The pointer to the root node of the ast.
 * 
 * @var: initial_pipe: This is will be the prev_pipe in handle_pipes.
 * This is used to garantee that the first command will read from the stdin.
 * After the execution and the management of the pipes, prev_pipe will
 * update and its value will change, according to the number of pipes.
 * @var: executed: This is a boolean that indicates if the command has been
 * executed. This is used in the case of redirection failed and is followed by
 * a pipe, exclusive for that case.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

static void	handle_cmd(t_exec *exec, t_hashtable *hash, t_ast *root)
{
	int	initial_pipe[2];
	t_bool executed;

	initial_pipe[0] = -1;
	initial_pipe[1] = -1;
	executed = false;
	
	if (root->type == TYPE_COMMAND)
		exec_forked_cmd(exec, hash, root);
	if (root->type == TYPE_REDIRECT)
	{
		exec->error_call = handle_redirects(root);
		if (exec->error_call == 1 && exec->count_pipes == 1)
		{
			g_global.cmd_status = 2;
			if (exec_multi_cmds(exec, hash, root->right) == 0)
				return ;
			executed = true;
		}
		if (executed)
			return ;
		g_global.cmd_status = analyze_redirect(exec, hash, root);
	}
	if (root->type == TYPE_PIPE)
	{
		create_files(root, exec, 0);
		handle_pipes(hash, exec, root, initial_pipe);
	}
	if (root->type == TYPE_LOGICAL)
	{
		handle_logical(exec, hash, root);
		restore_fd(exec->old_stdin, exec->old_stdout);
	}
}

/**
 * Function: exec_multi_cmds
 * -----------------
 * This function is used to encapsulate the execution of the ast. It is used
 * to execute the ast, and to wait for the children processes. 
 * 
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: hash: The pointer to the hashtable.
 * @param: root: The pointer to the root node of the ast.
 * 
 * @return: Returns an int that indicates the exit status of the last command.
 *
 */

int	exec_multi_cmds(t_exec *exec, t_hashtable *hashtable, t_ast *root)
{
	if (root == NULL)
		return (0);
	if (heredoc_first(exec, hashtable, root) && root->type == TYPE_PIPE)
	{
		wait_for_children(root);
		close_all_fds();
		return (0);
	}
	handle_cmd(exec, hashtable, root);
	wait_for_children(root);
	return (g_global.exit_status);
}

/**
 * Function: exec_forked_cmd
 * -----------------
 * This function is used only by the basic command of the ast, aka 'echo hello'.
 * It is used to execute the command in a forked process. If the command is a
 * builtin, it will execute the builtin. If the command is not a builtin, it
 * will execute the command with execve. If the command is not found, it will
 * return 127. If the command is found but it has not the permissions to be
 * executed, it will return 126. If the command is found but it has an error
 * during the execution, it will return 2.
 * 
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: hash: The pointer to the hashtable.
 * @param: root: The pointer to the root node of the ast.
 * 
 * @return: Returns an int that indicates the exit status of the last command.
 *
 */

int	exec_forked_cmd(t_exec *exec, t_hashtable *hash, t_ast *node)
{
	if (is_builtin(node))
	{
		execute_builtin(hash, node);
		return (g_global.exit_status);
	}
	if (analyze_cmd(hash, node) != 0)
		return (g_global.cmd_status);
	else
		g_global.cmd_status = forking(exec, hash, node);
	return (g_global.exit_status);
}

/**
 * Function: forking
 * -----------------
 * This function is an aux function of exec_forked_cmd. It is used to fork the
 * process and to execute the command in the child process. 
 * 
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: hash: The pointer to the hashtable.
 * @param: root: The pointer to the root node of the ast.
 * 
 * @return: Returns an int that indicates the exit status of the last command.
 *
 */

int	forking(t_exec *exec, t_hashtable *hash, t_ast *node)
{
	node->pid = fork();
	if (node->type == TYPE_COMMAND)
	{
		if (node->pid == 0)
		{
			if (node->path == NULL)
				g_global.cmd_status = 127;
			else
			{
				if (execve(node->path, node->args, NULL) == -1)
					g_global.cmd_status = 2;
			}
			free_for_finish(exec, hash);
			exit(g_global.cmd_status);
		}
	}
	return (g_global.cmd_status);
}
