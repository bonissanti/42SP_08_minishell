/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:40:43 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/15 13:45:51 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast	*init_ast(t_cmd_list *cmd_list, t_exec *exec)
{
	t_ast		*ast;
	t_cmd_list	*head;

	ast = NULL;
	head = cmd_list;
	while (head)
	{
		if (head->type == TYPE_FILE)
			head = head->next;
		if (head)
		{
			insert_ast(&ast, create_node(head), exec);
			head = head->next;
		}
	}
	return (ast);
}

t_ast	*create_node(t_cmd_list *cmd_list)
{
	t_ast	*new_node;

	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	prepare_ast(new_node, cmd_list);
	new_node->path = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->num_status = 0;
	new_node->in_fd = -1;
	new_node->out_fd = -1;
	new_node->pid = 0;
	if (new_node->type != TYPE_SUBSHELL)
		new_node->subshell = false;
	new_node->print_hdoc = false;
	new_node->print_redir = false;
	new_node->to_exec = true;
	return (new_node);
}

void	insert_ast(t_ast **head, t_ast *new_node, t_exec *exec)
{
	t_ast	*current;

	if (*head == NULL)
		*head = new_node;
	else if (new_node->weight > (*head)->weight)
	{
		new_node->left = *head;
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current && current->right != NULL
			&& current->right->weight >= new_node->weight)
			current = current->right;
		new_node->left = current->right;
		current->right = new_node;
	}
	if (new_node->type == TYPE_PIPE)
		exec->count_pipes++;
	else if (new_node->type == TYPE_HEREDOC)
		exec->count_hdoc++;
	exec->error_call = 0;
}

void	delete_node(t_ast *head)
{
	if (head != NULL)
	{
		delete_node(head->left);
		delete_node(head->right);
		safe_free((void **)&head->path);
		if (head)
			free(head);
	}
}
