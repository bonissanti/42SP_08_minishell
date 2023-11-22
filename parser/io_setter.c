/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_setter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:16:57 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/21 15:20:45 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

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
		if(head && head->type == TYPE_OPERATOR)
			*cmd_list = head;
	}
}
