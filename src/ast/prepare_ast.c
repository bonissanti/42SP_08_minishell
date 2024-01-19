/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:35:28 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/17 15:24:01 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: prepare_command
 * -----------------
 * This function is used to prepare a command node for our AST.
 *  
 * @param: **new_node: The node that will be prepared to carry a
 * command type data.
 * @param: *cmd_list: The cmd_list node that has all data needed to
 * create the new AST node.
 * 
 * @return: Returns nothing.
 *
 */

static void	prepare_command(t_ast *new_node, t_cmd_list *cmd_list)
{
	new_node->cmds = new_node->args[0];
	if (cmd_list->here_doc)
		new_node->delim = cmd_list->infile;
	else
		new_node->infile = cmd_list->infile;
	new_node->outfile = cmd_list->outfile;
	new_node->weight = cmd_list->weight;
	new_node->type = cmd_list->type;
}

/**
 * Function: prepare_subshell
 * -----------------
 * This function is used to prepare a subshell node for our AST.
 *  
 * @param: **new_node: The node that will be prepared to carry a
 * command type data.
 * @param: *cmd_list: The cmd_list node that has all data needed to
 * create the new AST node.
 * 
 * @return: Returns nothing.
 *
 */

static void	prepare_subshell(t_ast *new_node, t_cmd_list *cmd_list)
{
	new_node->cmds = new_node->args[0];
	new_node->subshell = true;
	new_node->weight = cmd_list->weight;
	new_node->type = cmd_list->type;
}

/**
 * Function: prepare_redirect_or_heredoc
 * -----------------
 * This function is used to prepare a redirect or heredoc node for our AST.
 *  
 * @param: **new_node: The node that will be prepared to carry a
 * command type data.
 * @param: *cmd_list: The cmd_list node that has all data needed to
 * create the new AST node.
 * 
 * @return: Returns nothing.
 *
 */

static void	prepare_redirect_or_heredoc(t_ast *new_node, t_cmd_list *cmd_list)
{
	t_shell	*shell;

	shell = get_shell();
	new_node->cmds = new_node->args[0];
	if (cmd_list->type == TYPE_REDIRECT)
	{
		new_node->infile = cmd_list->infile;
		analyzing_quotes(shell->hash, shell, &new_node->infile);
		new_node->outfile = cmd_list->outfile;
		analyzing_quotes(shell->hash, shell, &new_node->outfile);
	}
	else if (cmd_list->type == TYPE_HEREDOC)
	{
		new_node->delim = cmd_list->next->args;
		analyzing_quotes(shell->hash, shell, &new_node->delim);
	}
	new_node->weight = cmd_list->weight;
	new_node->type = cmd_list->type;
}

/**
 * Function: is_blank_command
 * -----------------
 * This function is used to assist the prepare_ast function to check
 * if the command passed is a sequence of e blank spaces.
 *  
 * @param: *cmd: The command to be analyzed.
 * 
 * @return: Returns 1 if the function gets to the last char whithout
 * find any char different of blank space "ascii 32", 0 otherwise.
 *
 */

int	is_blank_command(const char *cmd)
{
	if (*cmd != 32)
		return (0);
	while (*cmd == 32 && *cmd)
	{
		if (*cmd != 32)
			return (0);
		cmd++;
	}
	return (1);
}

/**
 * Function: prepare_ast
 * -----------------
 * This function is used to manage the creation of AST nodes.
 *  
 * @param: *new_node: The node created by the create_node function
 * to be prepared as one of the node types.
 * @param: *cmd_list: The cmd_list node that has all data needed to
 * create the new AST node.
 * 
 * @var: *shell: The static variable that is holding all the data that
 * is being shared between the functions.
 * @var: i: The iterator for this function.
 * 
 * @return: Returns nothing.
 *
 */

void	prepare_ast(t_ast *new_node, t_cmd_list *cmd_list)
{
	t_shell	*shell;
	int		i;

	i = -1;
	shell = get_shell();
	if (is_blank_command(cmd_list->args))
		new_node->args = matrix_to_free(ast_split(cmd_list->args, '\n'));
	else if (ft_strlen(cmd_list->args) > 0)
		new_node->args = matrix_to_free(ast_split(cmd_list->args, ' '));
	else
		new_node->args = matrix_to_free(ast_split(cmd_list->args, '\n'));
	shell->count_args = ft_count_args(new_node->args);
	while (new_node->args[++i])
	{
		analyzing_quotes(shell->hash, shell, &new_node->args[i]);
		if (shell->to_exec == 2)
			return ;
	}
	if (cmd_list->type == TYPE_COMMAND)
		prepare_command(new_node, cmd_list);
	else if (cmd_list->type == TYPE_SUBSHELL)
		prepare_subshell(new_node, cmd_list);
	else
		prepare_redirect_or_heredoc(new_node, cmd_list);
}
