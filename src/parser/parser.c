/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:21:28 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/08 18:20:48 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	command_consistency(t_tkn_list *tokenized)
{
	t_tkn_list	*head;
	t_tkn_list	*tail;

	if (!tokenized)
	{
		g_global.to_exec = 2;
		return ;
	}
	head = tokenized;
	tail = last_tkn_list(tokenized);
	if (head->type == OR || head->type == AND || head->type == PIPE
		|| head->type == C_PARENTESIS)
	{
		ft_printf("syntax error near unexpected token `%s'\n",
			tkn_type_converter(head->type));
		g_global.to_exec = 2;
	}
	else if (tail->type == O_PARENTESIS || is_redirect(tail->type))
	{
		if (tail->type == O_PARENTESIS)
			ft_printf("syntax error near unexpected token `%s'\n",
				tkn_type_converter(tail->type));
		else
			ft_printf("syntax error near unexpected token `newline'\n");
		g_global.to_exec = 2;
	}
}

t_cmd_list	*rewind_list(t_cmd_list **cmd_list)
{
	if ((*cmd_list)->prev == NULL)
		return (*cmd_list);
	else
	{
		while ((*cmd_list)->prev != NULL)
			*cmd_list = (*cmd_list)->prev;
	}
	return (*cmd_list);
}

void	join_args(t_tkn_list *tkn_list)
{
	t_tkn_list	*current;

	if (!tkn_list)
		return ;
	current = tkn_list;
	while (current)
	{
		if (current && (current->type == IDENTIFIER || current->type == EXPAND
				|| current->type == WILD))
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

void	move_to_front(t_cmd_list **head, t_cmd_list *search_node)
{
	t_cmd_list	*prev;
	t_cmd_list	*cur;

	prev = NULL;
	cur = *head;
	if (cur->next->type == TYPE_FILE
		&& cur->next->next->type != TYPE_COMMAND)
		return ;
	while (cur != NULL && cur != search_node)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur != NULL)
	{
		prev->next = cur->next;
	}
	search_node->next = *head;
	*head = search_node;
}

void	parser(t_hashtable *env)
{
	(void)env;
	command_consistency(g_global.tkn_list);
	if (g_global.to_exec == 2)
		g_global.cmd_status = 2;
	if (g_global.to_exec != 2)
		join_args(g_global.tkn_list);
	else
		return ;
	if (g_global.cmd_list->type == TYPE_HEREDOC && g_global.cmd_list->next)
	{
		if (g_global.cmd_list->next->next)
			move_to_front(&g_global.cmd_list, g_global.cmd_list->next->next);
	}
}
