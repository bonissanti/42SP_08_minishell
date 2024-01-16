/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:40:43 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/15 20:39:29 by aperis-p         ###   ########.fr       */
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

/**
 * Function: Create_node
 * -----------------
 * This function is used create a new node for the AST.
 * Each node will have a type, a value and a pointer to the left and right
 * nodes. 
 *  
 * @param: type: The type of the node, it can be TYPE_COMMAND, TYPE_FILE,
 * TYPE_REDIRECT or TYPE_OPERATOR.
 * @param: *args: The value of the node, it can be the command, the file,
 * the redirect or the operator name.
 * @param: op: The operator of the node, it can be OP_REDIRECT, OP_PIPE,
 * OP_LOGICAL or DEFAULT.
 * 
 * @var: new_node: The new node to be created.
 * 
 * @return: Returns a pointer to the new node.
 *
 */

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

/**
 * Function: Insert_ast
 * -----------------
 * This function is used to insert the new node in the AST. The insertion
 * is done in a sorted way, so the nodes will be sorted by their operator
 * precedence. The nodes with lower precedence will be on the top of the
 * tree, and the nodes with higher precedence will be on the bottom.
 * 
 * Insert ast has two cases:
 * 1. Left: When the new node has higher precedence than the head node, the new
 * node will be the new head node and the old head node will be the left.
 * 
 * 2. Right: head will have the operator with the lowest precedence, so the 
 * second line of nodes, needs to have the second lowest precedence (if exists),
 * if not, than the second line of needs needs to be occupied by the highest
 * precedence node. To do this, we need to pass the right node of the head
 * to the left node, then the new node will be the right node of the head.
 * 
 *  
 * @param: **head: The head of the AST. It's a double pointer because we need
 * to change the head node when the new node has higher precedence.
 * @param: *new_node: The new node to be inserted.
 * 
 * @var: current: The current node of the AST.
 * 
 * @return: Returns nothing.
 *
 */

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

/**
 * Function: Delete_node
 * -----------------
 * This function is used to free the memory of the node. First it checks if
 * the node is not NULL, then it frees the memory of the node and the args.
 * 
 * @param: *node: The node to be deleted.
 *  * 
 * @return: Returns nothing.
 *
 */

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
