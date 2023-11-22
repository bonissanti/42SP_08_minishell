/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:32:41 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/22 17:43:09 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd_list *find_command(t_cmd_list *cmd_list)
{
	while(cmd_list && cmd_list->type != TYPE_COMMAND)
		cmd_list = cmd_list->next;
	if(!cmd_list)
		return(NULL);
	else if (cmd_list->type == TYPE_COMMAND)
		return(cmd_list);
	else
		return(NULL);
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
			// g_global.cmd_list = last_cmd_list(g_global.cmd_list);
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
			.weight = DEFAULT,
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
			.weight = DEFAULT,
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
		.weight = OP_REDIRECT,
		.here_doc = has_here_doc,
	});
	*current = (*current)->next;
}

void	new_subshell_node(t_tkn_list **current)
{
	add_cmd_list((t_cmd_list){
		.type = TYPE_OPERATOR,
		.args = tkn_type_converter((*current)->type),
		.weight = DEFAULT,
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
		.weight = weight,
	});
	*current = (*current)->next;
}