/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:40:43 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/01 19:26:36 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"


static void	prepare_ast(t_ast *new_node, char *cmds, t_type type)
{
	new_node->split = ast_split(cmds, ' ');
	if (type == TYPE_REDIRECT)
	{
		new_node->cmds = new_node->split[0];
		new_node->delim = new_node->split[1];
		new_node->args = NULL;
	}
	else
	{
		new_node->cmds = new_node->split[0];
		new_node->args = new_node->split + 1;
		new_node->delim = NULL;
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


t_ast *create_node(t_type type, char *cmds, t_op weight)
{
	t_ast *new_node;
	
	new_node = (t_ast *)malloc(sizeof(t_ast));
	prepare_ast(new_node, cmds, type);
	new_node->path = NULL;
	new_node->weight = weight;
	new_node->type = type;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->exit_status = 0;
	new_node->fd = 0;
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

void insert_ast(t_ast **head, t_ast *new_node, t_exec *exec)
{
	t_ast *current;
	
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
		while (current->right != NULL && current->right->weight 
			>= new_node->weight)
			current = current->right;
		new_node->left = current->right;
		current->right = new_node;
	}

	if (new_node->type == TYPE_COMMAND)
		exec->cmd_count++;
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

void delete_node(t_ast *head)
{
	if (head != NULL)
	{
		delete_node(head->left);
		delete_node(head->right);
		free_split(head->split);
		safe_free((void **)&head->path);
		free(head);
	}
}


// void in_order_traversal(t_ast *head)
// {
// 	if (head != NULL)
// 	{
// 		in_order_traversal(head->left);
// 		printf("%s\n", head->args);
// 		in_order_traversal(head->right);
// 	}
// }

void pre_order_traversal(t_ast *head)
{
	if (head != NULL)
	{
		printf("%s\n", head->cmds);
		pre_order_traversal(head->left);
		pre_order_traversal(head->right);
	}
}

// void post_order_traversal(t_ast *head)
// {
// 	if (head != NULL)
// 	{
// 		post_order_traversal(head->left);
// 		post_order_traversal(head->right);
// 		printf("%s\n", head->args);
// 	}
// }

// void print_tree(t_ast *head, int depth)
// {
// 	int i = -1;
// 	if (head != NULL)
// 	{
// 		print_tree(head->left, depth + 1);
// 		while (++i < depth)
// 			printf("   ");
// 		printf("%s\n", head->args);
// 		print_tree(head->right, depth + 1);
// 	}
// }

// int main(void)
// {
//     t_ast *head = NULL;

//     t_ast *node1 = create_node(TYPE_COMMAND, "ls -l", DEFAULT);
//     insert_ast(&head, node1);

//     t_ast *node2 = create_node(TYPE_OPERATOR, ">", OP_REDIRECT);
//     insert_ast(&head, node2);

//     t_ast *node3 = create_node(TYPE_FILE, "error.txt", DEFAULT);
//     insert_ast(&head, node3);

//     t_ast *node4 = create_node(TYPE_OPERATOR, "&&", OP_LOGICAL);
//     insert_ast(&head, node4);

//     t_ast *node5 = create_node(TYPE_COMMAND, "cat error.txt", DEFAULT);
//     insert_ast(&head, node5);

//     t_ast *node6 = create_node(TYPE_OPERATOR, "|", OP_PIPE);
//     insert_ast(&head, node6);

//     t_ast *node7 = create_node(TYPE_COMMAND, "grep \"42\"", DEFAULT);
//     insert_ast(&head, node7);

//     pre_order_traversal(head);
// 	delete_node(head);

//     return (0);
// }


//ls -l > outfile.txt < cat | wc -l
// int main(void)
// {
// 	t_ast *head = create_node(TYPE_COMMAND, "ls -l");

// 	t_ast *node1 = create_node(TYPE_OPERATOR, "|");
// 	insert_ast(&head, node1, OP_PIPE);

// 	t_ast *node2 = create_node(TYPE_FILE, "grep .c");
// 	insert_ast(&head, node2, DEFAULT);

// 	t_ast *node3 = create_node(TYPE_OPERATOR, "&&");
// 	insert_ast(&head, node3, OP_LOGICAL);

// 	t_ast *node4 = create_node(TYPE_COMMAND, "wc -l");
// 	insert_ast(&head, node4, DEFAULT);

// 	t_ast *node5 = create_node(TYPE_OPERATOR, ">");
// 	insert_ast(&head, node5, OP_REDIRECT);

// 	t_ast *node6 = create_node(TYPE_FILE, "output.txt");
// 	insert_ast(&head, node6, DEFAULT);

// 	pre_order_traversal(head);
// 	// print_tree(head, 0);
// 	return (0);
// }


//ls -l > outfile.txt < cat | wc -l
// int main(void)
// {
// 	t_ast *head = create_node(NODE_COMMAND, "ls -l");

// 	t_ast *node1 = create_node(NODE_OPERATOR, "|");
// 	insert_ast(&head, node1, OP_PIPE);

// 	t_ast *node2 = create_node(NODE_FILE, "grep .c");
// 	insert_ast(&head, node2, DEFAULT);

// 	t_ast *node3 = create_node(NODE_OPERATOR, "&&");
// 	insert_ast(&head, node3, OP_LOGICAL);

// 	t_ast *node4 = create_node(NODE_COMMAND, "wc -l");
// 	insert_ast(&head, node4, DEFAULT);

// 	t_ast *node5 = create_node(NODE_OPERATOR, ">");
// 	insert_ast(&head, node5, OP_REDIRECT);

// 	t_ast *node6 = create_node(NODE_FILE, "output.txt");
// 	insert_ast(&head, node6, DEFAULT);

// 	pre_order_traversal(head);
// 	// print_tree(head, 0);
// 	return (0);
// }

// int main(void)
// {
// 	t_ast *head = create_node(NODE_COMMAND, "ls");

// 	t_ast *node1 = create_node(NODE_OPERATOR, "|");
// 	insert_ast(&head, node1, OP_PIPE);

// 	t_ast *node2 = create_node(NODE_COMMAND, "grep .c");
// 	insert_ast(&head, node2, OP_PIPE);

// 	print_tree(head, 0);
// 	delete_node(head);
// 	delete_node(node1);
// 	delete_node(node2);
// 	return (0);
// }