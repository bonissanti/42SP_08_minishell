/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:21:28 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/21 19:53:42 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	command_consistency(t_tkn_list *tokenized)
{
	t_tkn_list *head;
	t_tkn_list *tail;

	head = tokenized;
	tail = last_tkn_list(tokenized);
	if(head->type ==  OR || head->type == AND
	|| head->type == PIPE || head->type == C_PARENTESIS)
	{
		ft_printf("syntax error near unexpected token `%s'\n", tkn_type_converter(head->type));
		exit(2);
	}
	else if (tail->type == OR || tail->type == AND 
	|| tail->type == PIPE || tail->type == O_PARENTESIS)
	{
		ft_printf("syntax error near unexpected token `%s'\n", tkn_type_converter(tail->type));
		exit(2);
	}
	return (1);
}

t_cmd_list *rewind_list(t_cmd_list **cmd_list)
{
	if((*cmd_list)->prev == NULL)
		return (*cmd_list);
	else
	{
		while((*cmd_list)->prev != NULL)
			*cmd_list = (*cmd_list)->prev;
	}
	return(*cmd_list);
}

void	join_args(t_tkn_list *tkn_list)
{
	t_tkn_list	*current;
	
	current = tkn_list;
	while(current)
	{
		if (current && (current->type == IDENTIFIER
		|| current->type == EXPAND || current->type == WILD))
			new_cmd_file_node(&current);
		if (current && is_redirect(current->type))
			new_redirect_node(&current);
		if (current && current->type == O_PARENTESIS)
			new_subshell_node(&current);
		if (current && is_operator(current->type))
			new_operator_node(&current);
	}
	set_io(&(g_global).cmd_list);
	rewind_list(&(g_global).cmd_list);
}

void parser(t_hashtable *env)
{
	(void)env;
	command_consistency(g_global.tkn_list);
	join_args(g_global.tkn_list);
	print_cmd_list(g_global.cmd_list);
}
