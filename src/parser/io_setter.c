/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_setter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:16:57 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/14 16:50:14 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: set_command_input
 * 
 * The set_command_input is a subfunction of the set_io function
 * it sets the infile and here_doc_fd fields of the TYPE_COMMAND
 * node in the cmd_list when cmd_list->args is '<' or "<<".
 * 
 * @param: **cmd_list: The command list.
 * @param: *head: The current head at the moment of the function call.
 * 
 * @return: void.
 * 
*/

void	set_command_input(t_cmd_list **cmd_list, t_cmd_list *head)
{
	while (*cmd_list && (*cmd_list)->type != TYPE_COMMAND)
		*cmd_list = (*cmd_list)->next;
	if (*cmd_list && (*cmd_list)->type == TYPE_COMMAND)
	{
		if (!head->here_doc && head->next && head->next->type == TYPE_FILE)
		{
			(*cmd_list)->infile = head->next->args;
			(*cmd_list)->here_doc_fd = 0;
			head->infile = head->next->args;
		}
		else if (head->here_doc)
		{
			(*cmd_list)->here_doc = true;
			(*cmd_list)->infile = head->next->args;
			(*cmd_list)->here_doc_fd = 42;
			head->infile = head->next->args;
		}
	}
}

/**
 * Function: set_command_output
 * 
 * The set_command_output is a subfunction of the set_io function,
 * it sets the outfile field of the TYPE_COMMAND node in the cmd_list
 * when cmd_list->args is '>' or ">>".
 * 
 * @param: **cmd_list: The command list.
 * @param: *head: The current head at the moment of the function call.
 * 
 * @return: void.
 * 
*/

void	set_command_output(t_cmd_list **cmd_list, t_cmd_list *head)
{
	while (*cmd_list && (*cmd_list)->type != TYPE_COMMAND)
		*cmd_list = (*cmd_list)->next;
	if (*cmd_list && (*cmd_list)->type == TYPE_COMMAND)
	{
		(*cmd_list)->outfile = head->next->args;
		head->outfile = head->next->args;
	}
}

/**
 * Function: set_io
 * 
 * The set_io function sets the infile, outfile and here_doc_fd fields
 * for each TYPE_COMMAND node that has a redirect in his command block.
 * 
 * @param: **cmd_list: The command list.
 * 
 * @return: void.
 * 
*/

void	set_io(t_cmd_list **cmd_list)
{
	t_cmd_list	*head;
	t_cmd_list	*temp;
	t_cmd_list	*bkp;

	head = rewind_list(cmd_list);
	bkp = rewind_list(cmd_list);
	while (head)
	{
		temp = head->next;
		if ((head->type == TYPE_REDIRECT || head->type == TYPE_HEREDOC)
			&& (!ft_strncmp(head->args, "<<", 2) || *(*head).args == '<'))
			set_command_input(cmd_list, head);
		else if (head->type == TYPE_REDIRECT && (!ft_strncmp(head->args, ">>",
					2) || *(*head).args == '>'))
			set_command_output(cmd_list, head);
		head = temp;
		if (head && (head->type == TYPE_PIPE || head->type == TYPE_LOGICAL))
			*cmd_list = head;
	}
	*cmd_list = bkp;
}
