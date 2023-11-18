/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:21:28 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/18 01:20:47 by aperis-p         ###   ########.fr       */
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
			*cmd_list = (*cmd_list)->prev; // infinite loop here
	}
	return(*cmd_list);
}

void set_command_input(t_cmd_list **cmd_list, t_cmd_list *head)
{
	while((*cmd_list)->type != TYPE_COMMAND)
		*cmd_list = (*cmd_list)->next;
	if (!head->here_doc && head->next->type == TYPE_FILE)
	{
		(*cmd_list)->infile = head->next->args;
		(*cmd_list)->here_doc_fd = 0;
	}
	else if	(head->here_doc)
	{
		(*cmd_list)->infile = NULL;
		(*cmd_list)->here_doc_fd = 42;
	}
}

void set_command_output(t_cmd_list **cmd_list, t_cmd_list *head)
{
	while((*cmd_list)->type != TYPE_COMMAND)
		*cmd_list = (*cmd_list)->next;
	(*cmd_list)->outfile = head->next->args;
}

void set_io(t_cmd_list **cmd_list)
{
	t_cmd_list *head;
	t_cmd_list *temp;

	head = rewind_list(cmd_list);
	while(head)
	{
		temp = head->next;
		if (head->type == TYPE_REDIRECT && (!ft_strncmp(head->args, "<<", 2) || *(*head).args == '<'))
			set_command_input(cmd_list, head);
		else if (head->type == TYPE_REDIRECT && (!ft_strncmp(head->args, ">>", 2) || *(*head).args == '>'))
			set_command_output(cmd_list, head);
		head = temp;		
	}
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
	// while(g_global.cmd_list->next)
	// {
	// 	is_quotes(env, &g_global.cmd_list->args);
	// 	g_global.cmd_list = g_global.cmd_list->next;
	// }
	// is_quotes(env, &g_global.cmd_list->args);
	// rewind_list(&(g_global).cmd_list);
	print_cmd_list(g_global.cmd_list);
}
