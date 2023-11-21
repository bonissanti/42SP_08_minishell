/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:32:41 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/20 22:51:06 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd_list *find_command(t_cmd_list *cmd_list)
{
	t_cmd_list *current_command;
	
	current_command = NULL;
	while(cmd_list)
	{
		if(cmd_list->type == TYPE_COMMAND)
			current_command = cmd_list;
		else if(cmd_list->type == TYPE_OPERATOR)
			current_command = NULL;
		cmd_list = cmd_list->next;
	}
	return(current_command);
}

void append_expand(t_tkn_list **current)
{
	while(*current && ((*current)->type == IDENTIFIER || (*current)->type == EXPAND || (*current)->type == WILD))
	{			
		if(!*current)
			return ;
		if((*current)->type != IDENTIFIER && (*current)->type != EXPAND && (*current)->type != WILD)
			return ;	
		else
		{
			g_global.cmd_list = find_command(g_global.cmd_list);
			g_global.cmd_list->args = gnl_strjoin(g_global.cmd_list->args, " ");
			g_global.cmd_list->args = gnl_strjoin(g_global.cmd_list->args, (*current)->content);
		}
		*current = (*current)->next;
	}
}

void new_cmd_file_node(t_tkn_list **current)
{
	if(tkn_list_size((*current)->prev) && is_redirect((*current)->prev->type))
	{
		add_cmd_list((t_cmd_list){
			.type = TYPE_FILE,
			.args = (*current)->content,
			.prec_weight = DEFAULT,
			});
		*current = (*current)->next;
		return ;
	}
	else if(find_command(g_global.cmd_list))
	{
		append_expand(current);
			if(!(*current))
				return ;
	}
	else
	{			
		add_cmd_list((t_cmd_list){
			.type = TYPE_COMMAND,
			.args = (*current)->content,
			.prec_weight = DEFAULT,
		});
		*current = (*current)->next;
	}
}

void	new_redirect_node(t_tkn_list **current)
{
	t_bool has_here_doc;
		
	if((*current)->type == HERE_DOC)
		has_here_doc = true;
	else
		has_here_doc = false;
	add_cmd_list((t_cmd_list){
		.type = TYPE_REDIRECT,
		.args = tkn_type_converter((*current)->type),
		.prec_weight = OP_REDIRECT,
		.here_doc = has_here_doc,
	});
	*current = (*current)->next;
}

void	new_subshell_node(t_tkn_list **current)
{
	add_cmd_list((t_cmd_list){
		.type = TYPE_OPERATOR,
		.args = tkn_type_converter((*current)->type),
		.prec_weight = DEFAULT,
	});
	*current = (*current)->next;
	while((*current)->type != C_PARENTESIS)
	{
		g_global.cmd_list = last_cmd_list(g_global.cmd_list);
		g_global.cmd_list->args = gnl_strjoin(g_global.cmd_list->args, (*current)->content);
		if((*current)->next->type != C_PARENTESIS)
			g_global.cmd_list->args = gnl_strjoin(g_global.cmd_list->args, " ");
		*current = (*current)->next;
	}
	g_global.cmd_list->args = gnl_strjoin(g_global.cmd_list->args, tkn_type_converter((*current)->type));
	*current = (*current)->next;
}

void	new_operator_node(t_tkn_list **current)
{
	t_operator weight;
	
	if ((*current)->type == PIPE)
		weight = OP_PIPE;
	else
		weight = OP_LOGICAL;
	add_cmd_list((t_cmd_list){
		.type = TYPE_OPERATOR,
		.args = tkn_type_converter((*current)->type),
		.prec_weight = weight,
	});
	*current = (*current)->next;
}