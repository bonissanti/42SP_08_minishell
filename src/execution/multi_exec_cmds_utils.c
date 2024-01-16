/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:35:32 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/15 20:48:28 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: exec_simple
 * -----------------
 * This is the most used function in the execution. It is similar to the
 * exec_forked_cmd, but it does not fork, because this happens outside of this
 * function. It is used to execute the simple commands, like ls, echo, etc.
 * And always is used after redirecting the fds in child process.
 * 
 * @param: exec: The pointer to the exec struct, aux struct for the execution.
 * @param: hash: The pointer to the hashtable.
 * @param: root: The pointer to the root node of the ast.
 * 
 * @return: Returns an int that indicates the exit status of the last command.
 *
 */

int	exec_simple(t_hashtable *hash, t_exec *exec, t_ast *node)
{
	char	**envp;
	t_shell	*shell;

	shell = get_shell();
	envp = hashtable_to_envp(hash);
	if (analyze_cmd(hash, node, shell) != 0)
	{
		free_for_finish(exec, hash);
		free_envp(envp);
		return (shell->cmd_status);
	}
	if (is_builtin(node))
		execute_builtin(shell, node);
	else
	{
		shell->cmd_status = execve(node->path, node->args, envp);
		if (shell->cmd_status == -1)
			shell->cmd_status = 127;
		exit(shell->cmd_status);
	}
	free_envp(envp);
	free_for_finish(exec, hash);
	return (shell->cmd_status);
}

/**
 * Function: analyze_if_print
 * -----------------
 * This is used by the heredoc to set the print_hdoc to true in the nodes that
 * have a sequence of heredocs. It is used to print the line of the last heredoc
 * 
 * @param: root: The pointer to the root node of the ast.
 * @param: index: The index of the node that is being analyzed. (DEPRECATED).
 * @var: save_node: The pointer to the first node of the sequence of heredocs.
 * 
 * @return: Returns a void function.
 *
 */

void	analyze_if_print(t_ast *node, int index, t_exec *exec)
{
	t_ast	*save_node;

	save_node = node->left;
	while (node != NULL)
	{
		if (node->type == TYPE_HEREDOC && index == 0 && (node->right == NULL
				|| node->right->type != TYPE_HEREDOC))
		{
			if (node->left == NULL && exec->count_hdoc != 1)
				node->left = save_node;
			else if (!node->left && node->right
				&& !node->right->right && exec->count_hdoc == 1)
			{
				node->left = node->right;
				node->right = NULL;
			}
			node->print_hdoc = true;
		}
		node = node->right;
	}
}

/**
 * Function: redirect_fds
 * -----------------
 * This is used for the redirections. It redirects the fds of the node to the
 * stdin and stdout if they are not -1. In a nutshell, if the node is
 * different from -1, it means that the node has a redirection.
 * 
 * @param: node: The pointer to the root node of the ast.
 * 
 * @return: Returns a void function.
 *
 */

void	redirect_fds(t_ast *node)
{
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
}

/**
 * Function: close_all_fds
 * -----------------
 * This function is used to close all the fds that are not used in the execution
 * of the command, excepts the stdin, stdout and stderr.
 * 
 * @param: i: The index of the fd that is going to be closed.
 * 
 * @return: Returns a void function.
 *
 */

void	close_all_fds(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

t_bool	process_redirect(t_exec *exec, t_shell *shell, t_ast *node)
{
	exec->error_call = handle_redirects(node);
	if (exec->error_call == 1 && exec->count_pipes == 1)
	{
		shell->cmd_status = 2;
		if (exec_multi_cmds(exec, node->right, shell) == 0)
			return (true);
	}
	shell->cmd_status = analyze_redirect(exec, shell, node);
	return (false);
}
