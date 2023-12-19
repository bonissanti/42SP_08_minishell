/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:35:28 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/19 12:35:29 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static void	prepare_subshell(t_ast *new_node, t_cmd_list *cmd_list)
{
	new_node->cmds = new_node->args[0];
	new_node->subshell = true;
	new_node->weight = cmd_list->weight;
	new_node->type = cmd_list->type;
}

static void	prepare_redirect_or_heredoc(t_ast *new_node, t_cmd_list *cmd_list)
{
	new_node->cmds = new_node->args[0];
	if (cmd_list->type == TYPE_REDIRECT)
	{
		new_node->infile = cmd_list->infile;
		new_node->outfile = cmd_list->outfile;
	}
	else if (cmd_list->type == TYPE_HEREDOC)
		new_node->delim = cmd_list->infile;
	new_node->weight = cmd_list->weight;
	new_node->type = cmd_list->type;
}

void	prepare_ast(t_ast *new_node, t_cmd_list *cmd_list)
{
	new_node->args = ast_split(cmd_list->args, ' ');
	if (cmd_list->type == TYPE_COMMAND)
		prepare_command(new_node, cmd_list);
	else if (cmd_list->type == TYPE_SUBSHELL)
		prepare_subshell(new_node, cmd_list);
	else
		prepare_redirect_or_heredoc(new_node, cmd_list);
}
