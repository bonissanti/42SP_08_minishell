/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/08 14:40:25 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		after_hdoc(t_exec *exec, t_hashtable *hash, t_ast *node,
					char *filename);
static void		open_execute(t_hashtable *hash, t_exec *exec, t_ast *node,
					char *filename);

/**
 * Function: handle_heredoc
 * -----------------
 * This function is the heart of the heredoc redirection. It handles the
 * redirection of the input to a file, and then executes the commands that
 * follow the redirection. Besides, it calls the function checks the next
 * node, if it is a pipe, a redirection or a logical operator.
 *  
 * @param: hash: The pointer to the hashtable.
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: node: The pointer to the node that contains the redirection.
 * 
 * @var: line: The line that is read from the stdin.
 * @var: filename: The name of the file that is created to store the input.
 * @var: len: The length of the line.
 * @var: error_call: The error code returned by the function that creates the
 * file.
 * @var: print_hdoc: The boolean that indicates if the input should be printed
 * to the file.
 * 
 * @return: Returns 0 if the redirection is successful, 1 if there is an error
 *
 */

int	handle_heredoc(t_hashtable *hash, t_exec *exec, t_ast *node)
{
	char	*filename;

	filename = generate_filename(exec->count_hdoc);
	node->out_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	read_write_heredoc(hash, node);
	close(node->out_fd);
	exec->error_call = create_files(node, exec, 0);
	if ((exec->error_call == 1 || exec->error_call == -1)
		&& exec->count_pipes == 0)
	{
		free(filename);
		return (1);
	}
	if (node->print_hdoc && !node->right)
		open_execute(hash, exec, node, filename);
	after_hdoc(exec, hash, node, filename);
	return (0);
}

/**
 * Function: open_execute
 * -----------------
 * This function executes the commands that follow the heredoc redirection.
 * It is called by the function handle_heredoc.
 *  
 * @param: hash: The pointer to the hashtable.
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: node: The pointer to the node that contains the redirection.
 * @param: filename: The name of the file that is created to store the input.
 * 
 * @var: node->in_fd: The file descriptor of the file that stores the input.
 * @var: close(0): Closes the stdin, genereated by the restore_fd function in
 * the function exec_simple.
 * @var: close(1): Closes the stdout, genereated by the restore_fd function in
 * the function exec_simple.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

static void	open_execute(t_hashtable *hash, t_exec *exec, t_ast *node,
	char *filename)
{
	node->pid = fork();
	exec_signals(node->pid);
	if (node->pid == 0)
	{
		node->in_fd = open(filename, O_RDONLY);
		dup2(node->in_fd, STDIN_FILENO);
		close(node->in_fd);
		if (node->left)
			exec_simple(hash, exec, node->left);
		else
			free_for_finish(exec, hash);
		close_all_fds();
		free(filename);
		close(0);
		close(1);
		exit(0);
	}
	else
		free(filename);
}

/**
 * Function: After_hdoc
 * -----------------
 * This function executes the next node after the heredoc redirection. It is
 * called by the function handle_heredoc. It checks if the next node is a
 * redirection, a pipe or a logical operator.
 *  
 * @param: hash: The pointer to the hashtable.
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: node: The pointer to the node that contains the redirection.
 * @param: filename: The name of the file that is created to store the input.
 * 
 * @var: node->right->to_exec: The boolean that indicates if the next node
 * should be executed, it is setted to false or true by the function
 * handle_redirect in create_files.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

static void	after_hdoc(t_exec *exec, t_hashtable *hash, t_ast *node,
		char *filename)
{
	if (node->right && node->right->type == TYPE_HEREDOC)
	{
		free(filename);
		node->left = NULL;
		exec_multi_cmds(exec, hash, node->right);
	}
	else if (node->right && node->right->type == TYPE_REDIRECT)
		next_is_rdir(exec, hash, node, filename);
	else if (node->right && node->right->type == TYPE_PIPE)
		next_is_pipe(exec, hash, node, filename);
	if (node->right && node->right->type == TYPE_LOGICAL)
	{
		open_execute(hash, exec, node, filename);
		waitpid(node->pid, &node->num_status, 0);
		simple_logical(exec, hash, node->right, node->num_status);
	}
}

/**
 * Function: After_hdoc
 * -----------------
 * This function executes the next node after the heredoc redirection. It is
 * called by the function handle_heredoc. It checks if the next node is a
 * redirection, a pipe or a logical operator.
 *  
 * @param: hash: The pointer to the hashtable.
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: node: The pointer to the node that contains the redirection.
 * @param: filename: The name of the file that is created to store the input.
 * 
 * @var: node->right->to_exec: The boolean that indicates if the next node
 * should be executed, it is setted to false or true by the function
 * handle_redirect in create_files.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

void	parent_hdoc(t_exec *exec, t_hashtable *hash, t_ast *node,
		int *next_pipe)
{
	if (exec->count_pipes >= 1)
		close(next_pipe[1]);
	if (node->right && exec->count_pipes >= 1)
		node = find_node(node, TYPE_PIPE);
	if (exec->count_pipes >= 1)
	{
		exec->count_pipes--;
		handle_pipes(hash, exec, node->right, next_pipe);
	}
	restore_fd(exec->old_stdin, exec->old_stdout);
}
