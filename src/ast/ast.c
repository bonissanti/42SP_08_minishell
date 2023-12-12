/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:40:43 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/12 19:18:15 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast *init_ast(t_cmd_list *cmd_list, t_exec *exec, t_hashtable *env)
{
	t_ast *ast;
	t_cmd_list *head;

	// ast = ft_calloc(1, sizeof(t_ast));
	ast = NULL;
	head = cmd_list;
	while(head)
	{
		insert_ast(&ast, create_node(head, env), exec);
		head = head->next;
	}
	return(ast);
}

static void	prepare_ast(t_ast *new_node, t_cmd_list *cmd_list, t_hashtable *env)
{
	new_node->args = ast_split(cmd_list->args, ' ');
	
	if (cmd_list->type == TYPE_COMMAND)
	{
		analyzing_quotes(env, &new_node->args[0]); //is_quotes here?
		new_node->cmds = new_node->args[0];
		if(cmd_list->here_doc)
			new_node->delim = cmd_list->infile;
		else
			new_node->infile = cmd_list->infile;
		new_node->outfile = cmd_list->outfile;
		new_node->weight = cmd_list->weight;
		new_node->type = cmd_list->type;
	}
	else if (cmd_list->type == TYPE_SUBSHELL)
	{
		new_node->cmds = new_node->args[0];
		new_node->subshell = true;
		new_node->weight = cmd_list->weight;
		new_node->type = cmd_list->type;
	}
	else
	{
		new_node->cmds = new_node->args[0];
		new_node->weight = cmd_list->weight;
		new_node->type = cmd_list->type;
	}			
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

t_ast	*create_node(t_cmd_list *cmd_list, t_hashtable *env)
{
	t_ast	*new_node;

	new_node = (t_ast *)malloc(sizeof(t_ast));
	prepare_ast(new_node, cmd_list, env);
	new_node->path = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->num_status = 0;
	new_node->in_fd = -1;
	new_node->out_fd = -1;
	if(new_node->type != TYPE_SUBSHELL)
		new_node->subshell = false;
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
			&& current->right->weight >= new_node->weight) //SEGFAULT HERE
			current = current->right;
		new_node->left = current->right;
		current->right = new_node;
	}
	if (new_node->type == TYPE_PIPE && new_node->weight == OP_PIPE)
		exec->count_pipes++;
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
		free_split(head->args);
		safe_free((void **)&head->path);
		free(head);
	}
}
