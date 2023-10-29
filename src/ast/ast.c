/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:40:43 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/27 16:47:36 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast *create_node(t_ast_type type, char *args)
{
	t_ast *new_node;

	new_node = (t_ast *)malloc(sizeof(t_ast));
	new_node->type = type;
	new_node->args = args;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->op = DEFAULT;
	return (new_node);
}

void insert_ast(t_ast **root, t_ast *new_node, t_operator op)
{
	t_ast *current;

	if (*root == NULL)
	{
		*root = new_node;
		(*root)->op = op;
	}
	else if (op > (*root)->op)
	{
		new_node->left = *root;
		*root = new_node;
		(*root)->op = op;
	}
	else
	{
		current = *root;
		while (current->right != NULL && current->right->op >= op)
			current = current->right;
		new_node->left = current->right;
		current->right = new_node;
		new_node->op = op;
	}
}

void delete_node(t_ast *node)
{
	if (node != NULL)
	{
		free(node->args);
		free(node);
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

void post_order_traversal(t_ast *root)
{
	if (root != NULL)
	{
		post_order_traversal(root->left);
		post_order_traversal(root->right);
		printf("%s\n", root->args);
	}
}

void print_tree(t_ast *root, int depth)
{
	int i = -1;
	if (root != NULL)
	{
		print_tree(root->left, depth + 1);
		while (++i < depth)
			printf("   ");
		printf("%s\n", root->args);
		print_tree(root->right, depth + 1);
	}
}

int main(void)
{
    t_ast *root = NULL;

    t_ast *node1 = create_node(NODE_COMMAND, "ls -l");
    insert_ast(&root, node1, DEFAULT);

    t_ast *node2 = create_node(NODE_OPERATOR, ">");
    insert_ast(&root, node2, OP_REDIRECT);

    t_ast *node3 = create_node(NODE_FILE, "error.txt");
    insert_ast(&root, node3, DEFAULT);

    t_ast *node4 = create_node(NODE_OPERATOR, "&&");
    insert_ast(&root, node4, OP_LOGICAL);

    t_ast *node5 = create_node(NODE_COMMAND, "cat error.txt");
    insert_ast(&root, node5, DEFAULT);

    t_ast *node6 = create_node(NODE_OPERATOR, "|");
    insert_ast(&root, node6, OP_PIPE);

    t_ast *node7 = create_node(NODE_COMMAND, "grep \"42\"");
    insert_ast(&root, node7, DEFAULT);

    pre_order_traversal(root);
    return (0);
}


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