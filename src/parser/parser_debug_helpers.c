/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:27:30 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/11 14:43:47 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *tkn_type_string(t_tkn_type type)
{
	if(type == IDENTIFIER)
		return ("IDENTIFIER");
	else if(type == INFILE)
		return ("INFILE");
	else if(type == REDIRECT)
		return ("REDIRECT");
	else if(type == HERE_DOC)
		return ("HERE_DOC");
	else if(type == APPEND)
		return ("APPEND");
	else if(type == PIPE)
		return ("PIPE");
	else if(type == O_PARENTESIS)
		return ("O_PARENTESIS");
	else if(type == C_PARENTESIS)
		return ("C_PARENTESIS");
	else if(type == AND)
		return ("AND");
	else if(type == OR)
		return ("OR");
	else if(type == WILD)
		return ("WILD");
	else
		return ("EXPAND");
}
char *cmd_type_string(t_type type)
{
	if(type == TYPE_COMMAND)
		return ("TYPE_COMMAND");
	else if(type == TYPE_LOGICAL)
		return ("TYPE_LOGICAL");
	else if(type == TYPE_PIPE)
		return ("TYPE_PIPE");
	else if(type == TYPE_FILE)
		return ("TYPE_FILE");
	else 
		return ("TYPE_REDIRECT");
}

void print_tkn_list(t_tkn_list *tkn_list)
{
	ft_printf("---TKN_LIST---\n");
	while(tkn_list->next != NULL)
	{
		ft_printf("Token type: %s\nContent: %s\n ----------\n", 
		tkn_type_string(tkn_list->type), tkn_list->content);
		tkn_list = tkn_list->next;
	}
	ft_printf("Token type: %s\nContent: %s\n ----------\n\n", 
	tkn_type_string(tkn_list->type), tkn_list->content);
}

void print_cmd_list(t_cmd_list *cmd_list)
{
	ft_printf("---CMD_LIST---\n");
	while(cmd_list->next != NULL)
	{
		if(cmd_list->type == TYPE_COMMAND)
		{
			ft_printf("Type: %s\nArgs: %s\nweight: %d\n",
			cmd_type_string(cmd_list->type), cmd_list->args, cmd_list->weight);
			// if(cmd_list && cmd_list->type == TYPE_COMMAND && cmd_list->infile)
			// 	ft_printf("Infile: %s\n", cmd_list->infile);
			// if(cmd_list && cmd_list->type == TYPE_COMMAND && cmd_list->outfile)
			// 	ft_printf("Outfile: %s\n", cmd_list->outfile);
			// if(cmd_list && cmd_list->type == TYPE_COMMAND && cmd_list->here_doc_fd)
			// 	ft_printf("Here_doc: %d\n", cmd_list->here_doc_fd);
			// ft_printf("----------\n");
		}
			cmd_list = cmd_list->next;			
	}
	if(cmd_list->type == TYPE_COMMAND)
	{
		ft_printf("Type: %s\nArgs: %s\nweight: %d\n", 
		cmd_type_string(cmd_list->type), cmd_list->args, cmd_list->weight);
		// if(cmd_list && cmd_list->type == TYPE_COMMAND && cmd_list->infile)
		// 	ft_printf("Infile: %s\n", cmd_list->infile);
		// if(cmd_list && cmd_list->type == TYPE_COMMAND && cmd_list->outfile)
		// 	ft_printf("Outfile: %s\n", cmd_list->outfile);
		// if(cmd_list && cmd_list->type == TYPE_COMMAND && cmd_list->here_doc_fd)
		// 	ft_printf("Here_doc: %d\n", cmd_list->here_doc_fd);
		// ft_printf("----------\n");		
	}
}