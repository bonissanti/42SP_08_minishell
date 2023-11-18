/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:32:41 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/18 00:47:45 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void append_expand(t_tkn_list **current)
{
	while(*current && ((*current)->type == IDENTIFIER || (*current)->type == EXPAND || (*current)->type == WILD))
	{	
		*current = (*current)->next;
		if(!*current)
			return ;
		if((*current)->type != IDENTIFIER && (*current)->type != EXPAND && (*current)->type != WILD)
			return ;	
		else
		{
			g_global.cmd_list = last_cmd_list(g_global.cmd_list);
			g_global.cmd_list->args = gnl_strjoin(g_global.cmd_list->args, " ");
			g_global.cmd_list->args = gnl_strjoin(g_global.cmd_list->args, (*current)->content);
		}
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
			g_global.cmd_list->infile = NULL;
			g_global.cmd_list->outfile = NULL;
		*current = (*current)->next;
		return ;
	}
	else
	{
		add_cmd_list((t_cmd_list){
			.type = TYPE_COMMAND,
			.args = (*current)->content,
			.prec_weight = DEFAULT,
		});
		g_global.cmd_list->infile = NULL;
		g_global.cmd_list->outfile = NULL;
	}
	append_expand(current);
		if(!(*current))
			return ;
	// *current = (*current)->next;
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
	g_global.cmd_list->infile = NULL;
	g_global.cmd_list->outfile = NULL;
	*current = (*current)->next;
}

void	new_subshell_node(t_tkn_list **current)
{
	add_cmd_list((t_cmd_list){
		.type = TYPE_OPERATOR,
		.args = tkn_type_converter((*current)->type),
		.prec_weight = DEFAULT,
	});
	g_global.cmd_list->infile = NULL;
	g_global.cmd_list->outfile = NULL;
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
	g_global.cmd_list->infile = NULL;
	g_global.cmd_list->outfile = NULL;
	*current = (*current)->next;
}