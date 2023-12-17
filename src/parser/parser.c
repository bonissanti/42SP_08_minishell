/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:21:28 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/11 16:27:41 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: command_consistency
 * -----------------
 * The command_consistency function checks if the tkn_list
 * has an operator or a wrong parentesis at the beggining 
 * or at the end of the list.
 * 
 * @param: *tokenized: A pointer to the tokenized list.
 * 
 * @return: int.
 * 
*/

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
		return (2);
	}
	else if (tail->type == O_PARENTESIS || is_redirect(tail->type))
	{
		if (tail->type == O_PARENTESIS)
			ft_printf("syntax error near unexpected token `%s'\n", tkn_type_converter(tail->type));
		else
			ft_printf("syntax error near unexpected token `newline'\n");
		return (2);
	}
	return (1);
}

/**
 * Function: rewind_list
 * -----------------
 * The rewind_list function checks if the current head
 * is actually the first node of the list, if it is not
 * it iterates through the list until it finds the first
 * node.
 * 
 * @param: **cmd_list: A pointer to the cmd_list
 * 
 * @return: t_cmd_list *.
 * 
*/

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

/**
 * Function: join_args
 * -----------------
 * The join_args function iterates through the tokenized list
 * and form a brand new cmd_list by joining tokens that are of
 * the type IDENTIFIER, EXPAND or WILD, and filling then with
 * their respective data.
 * 
 * @param: *tkn_list: A pointer to the tokenized list.
 * @var: *current: A pointer to the current node of the list.
 * 
 * @return: void.
 * 
*/

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
}

/**
 * Function: parser
 * -----------------
 * The parser function is the main function of the parser.
 * It calls the command_consistency function to check if the
 * tkn_list is consistent, then it calls the join_args function
 * to form the cmd_list.
 * 
 * @param: *env: A pointer to the env.
 * 
 * @return: void.
 * 
*/

int parser(t_hashtable *env)
{
	int to_exec;

	(void)env;
	to_exec = command_consistency(g_global.tkn_list);
	join_args(g_global.tkn_list);
	// print_cmd_list(g_global.cmd_list);
	return (to_exec);
}
