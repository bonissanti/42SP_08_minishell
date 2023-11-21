/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:40:43 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/21 11:43:34 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"

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

t_ast *create_node(t_type type, char *args, t_operator op)
{
	t_ast *new_node;

	new_node = (t_ast *)malloc(sizeof(t_ast));
	new_node->type = type;
	new_node->path = NULL;
	new_node->args = args;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->op = op;
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
 * 1. Left: When the new node has higher precedence than the root node, the new
 * node will be the new root node and the old root node will be the left.
 * 
 * 2. Right: Root will have the operator with the lowest precedence, so the 
 * second line of nodes, needs to have the second lowest precedence (if exists),
 * if not, than the second line of needs needs to be occupied by the highest
 * precedence node. To do this, we need to pass the right node of the root
 * to the left node, then the new node will be the right node of the root.
 * 
 *  
 * @param: **root: The root of the AST. It's a double pointer because we need
 * to change the root node when the new node has higher precedence.
 * @param: *new_node: The new node to be inserted.
 * 
 * @var: current: The current node of the AST.
 * 
 * @return: Returns nothing.
 *
 */

void insert_ast(t_ast **root, t_ast *new_node)
{
	t_ast *current;

	if (*root == NULL)
		*root = new_node;
	else if (new_node->op > (*root)->op)
	{
		new_node->left = *root;
		*root = new_node;
	}
	else
	{
		current = *root;
		while (current->right != NULL && current->right->op >= new_node->op)
			current = current->right;
		new_node->left = current->right;
		current->right = new_node;
	}
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

void delete_node(t_ast *root)
{
	if (root != NULL)
	{
		delete_node(root->left);
		delete_node(root->right);
		free(root);
	}
}


// void in_order_traversal(t_ast *root)
// {
// 	if (root != NULL)
// 	{
// 		in_order_traversal(root->left);
// 		printf("%s\n", root->args);
// 		in_order_traversal(root->right);
// 	}
// }

void pre_order_traversal(t_ast *root)
{
	if (root != NULL)
	{
		printf("%s\n", root->args);
		pre_order_traversal(root->left);
		pre_order_traversal(root->right);
	}
}

// void post_order_traversal(t_ast *root)
// {
// 	if (root != NULL)
// 	{
// 		post_order_traversal(root->left);
// 		post_order_traversal(root->right);
// 		printf("%s\n", root->args);
// 	}
// }

// void print_tree(t_ast *root, int depth)
// {
// 	int i = -1;
// 	if (root != NULL)
// 	{
// 		print_tree(root->left, depth + 1);
// 		while (++i < depth)
// 			printf("   ");
// 		printf("%s\n", root->args);
// 		print_tree(root->right, depth + 1);
// 	}
// }

int main(void)
{
    t_ast *root = NULL;

    t_ast *node1 = create_node(TYPE_COMMAND, "ls -l", DEFAULT);
    insert_ast(&root, node1);

    t_ast *node2 = create_node(TYPE_OPERATOR, ">", OP_REDIRECT);
    insert_ast(&root, node2);

    t_ast *node3 = create_node(TYPE_FILE, "error.txt", DEFAULT);
    insert_ast(&root, node3);

    t_ast *node4 = create_node(TYPE_OPERATOR, "&&", OP_LOGICAL);
    insert_ast(&root, node4);

    t_ast *node5 = create_node(TYPE_COMMAND, "cat error.txt", DEFAULT);
    insert_ast(&root, node5);

    t_ast *node6 = create_node(TYPE_OPERATOR, "|", OP_PIPE);
    insert_ast(&root, node6);

    t_ast *node7 = create_node(TYPE_COMMAND, "grep \"42\"", DEFAULT);
    insert_ast(&root, node7);

    pre_order_traversal(root);
	delete_node(root);

    return (0);
}


//ls -l > outfile.txt < cat | wc -l
// int main(void)
// {
// 	t_ast *root = create_node(TYPE_COMMAND, "ls -l");

// 	t_ast *node1 = create_node(TYPE_OPERATOR, "|");
// 	insert_ast(&root, node1, OP_PIPE);

// 	t_ast *node2 = create_node(TYPE_FILE, "grep .c");
// 	insert_ast(&root, node2, DEFAULT);

// 	t_ast *node3 = create_node(TYPE_OPERATOR, "&&");
// 	insert_ast(&root, node3, OP_LOGICAL);

// 	t_ast *node4 = create_node(TYPE_COMMAND, "wc -l");
// 	insert_ast(&root, node4, DEFAULT);

// 	t_ast *node5 = create_node(TYPE_OPERATOR, ">");
// 	insert_ast(&root, node5, OP_REDIRECT);

// 	t_ast *node6 = create_node(TYPE_FILE, "output.txt");
// 	insert_ast(&root, node6, DEFAULT);

// 	pre_order_traversal(root);
// 	// print_tree(root, 0);
// 	return (0);
// }


//ls -l > outfile.txt < cat | wc -l
// int main(void)
// {
// 	t_ast *root = create_node(NODE_COMMAND, "ls -l");

// 	t_ast *node1 = create_node(NODE_OPERATOR, "|");
// 	insert_ast(&root, node1, OP_PIPE);

// 	t_ast *node2 = create_node(NODE_FILE, "grep .c");
// 	insert_ast(&root, node2, DEFAULT);

// 	t_ast *node3 = create_node(NODE_OPERATOR, "&&");
// 	insert_ast(&root, node3, OP_LOGICAL);

// 	t_ast *node4 = create_node(NODE_COMMAND, "wc -l");
// 	insert_ast(&root, node4, DEFAULT);

// 	t_ast *node5 = create_node(NODE_OPERATOR, ">");
// 	insert_ast(&root, node5, OP_REDIRECT);

// 	t_ast *node6 = create_node(NODE_FILE, "output.txt");
// 	insert_ast(&root, node6, DEFAULT);

// 	pre_order_traversal(root);
// 	// print_tree(root, 0);
// 	return (0);
// }

// int main(void)
// {
// 	t_ast *root = create_node(NODE_COMMAND, "ls");

// 	t_ast *node1 = create_node(NODE_OPERATOR, "|");
// 	insert_ast(&root, node1, OP_PIPE);

// 	t_ast *node2 = create_node(NODE_COMMAND, "grep .c");
// 	insert_ast(&root, node2, OP_PIPE);

// 	print_tree(root, 0);
// 	delete_node(root);
// 	delete_node(node1);
// 	delete_node(node2);
// 	return (0);
// }