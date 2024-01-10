/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:32:41 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/10 17:03:56 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	new_cmd_file_node(t_shell *shell, t_tkn_list **current)
{
	if (tkn_list_size((*current)->prev) && is_redirect((*current)->prev->type))
	{
		add_cmd_list(shell, (t_cmd_list){
			.type = TYPE_FILE,
			.args = (*current)->content,
			.weight = DEFAULT,
		});
		*current = (*current)->next;
	}
	else if (find_command(shell->cmd_list))
	{
		append_expand(shell, current);
		if (!(*current))
			return ;
	}
	else
	{
		add_cmd_list(shell, (t_cmd_list){
			.type = TYPE_COMMAND,
			.args = (*current)->content,
			.weight = DEFAULT,
			.anti_split = true,
		});
		*current = (*current)->next;
	}
}

void	new_redirect_node(t_shell *shell, t_tkn_list **current)
{
	t_bool	has_here_doc;
	t_op	weight;
	t_type	type;

	has_here_doc = false;
	weight = OP_REDIRECT;
	type = TYPE_REDIRECT;
	if ((*current)->type == HERE_DOC)
	{
		type = TYPE_HEREDOC;
		has_here_doc = true;
		weight = OP_HEREDOC;
	}
	else
		has_here_doc = false;
	add_cmd_list(shell, (t_cmd_list){
		.type = type,
		.args = tkn_type_converter((*current)->type),
		.weight = weight,
		.infile = (*current)->next->content,
		.outfile = (*current)->next->content,
		.here_doc = has_here_doc,
	});
	*current = (*current)->next;
}

void	new_subshell_node(t_shell *shell, t_tkn_list **current)
{
	add_cmd_list(shell, (t_cmd_list){
		.type = TYPE_SUBSHELL,
		.args = tkn_type_converter((*current)->type),
		.weight = DEFAULT,
	});
	*current = (*current)->next;
	while ((*current)->type != C_PARENTESIS)
	{
		shell->cmd_list = last_cmd_list(shell->cmd_list);
		shell->cmd_list->args = gnl_strjoin(shell->cmd_list->args,
				(*current)->content);
		if ((*current)->next->type != C_PARENTESIS)
			shell->cmd_list->args = gnl_strjoin(shell->cmd_list->args, " ");
		*current = (*current)->next;
	}
	shell->cmd_list->args = gnl_strjoin(shell->cmd_list->args,
			tkn_type_converter((*current)->type));
	*current = (*current)->next;
}

void	new_operator_node(t_shell *shell, t_tkn_list **current)
{
	t_op	weight;
	t_type	type_operator;

	if ((*current)->type == PIPE)
	{
		type_operator = TYPE_PIPE;
		weight = OP_PIPE;
	}
	else
	{
		type_operator = TYPE_LOGICAL;
		weight = OP_LOGICAL;
	}
	add_cmd_list(shell, (t_cmd_list){
		.type = type_operator,
		.args = tkn_type_converter((*current)->type),
		.weight = weight,
	});
	*current = (*current)->next;
}
