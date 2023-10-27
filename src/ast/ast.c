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

t_node *create_node(t_node_type type, char *args)
{
	t_node *new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->type = type;
	new_node->args = args;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void insert_node(t_node **root, t_node *new_node, t_operator op)
{
	if (*root == NULL)
		*root = new_node;
	else if (op > (*root)->type)
	{
		new_node->left = *root;
		*root = new_node;
	}
	else
		insert_node(&(*root)->right, new_node, op);
}

void delete_node(t_node *node)
{
	if (node != NULL)
	{
		free(node->args);
		free(node);
	}
}

void in_order_traversal(t_node *root)
{
	if (root != NULL)
	{
		in_order_traversal(root->left);
		printf("%s\n", root->args);
		in_order_traversal(root->right);
	}
}

void pre_order_traversal(t_node *root)
{
	if (root != NULL)
	{
		printf("%s\n", root->args);
		pre_order_traversal(root->left);
		pre_order_traversal(root->right);
	}
}

void post_order_traversal(t_node *root)
{
	if (root != NULL)
	{
		post_order_traversal(root->left);
		post_order_traversal(root->right);
		printf("%s\n", root->args);
	}
}

void print_tree(t_node *root, int depth)
{
	int i = -1;
	if (root != NULL)
	{
		print_tree(root->left, depth + 1);
		while (++i < depth)
			printf("   ");
		printf("%d\n", root->type);
		print_tree(root->right, depth + 1);
	}
}

int main(void)
{
	t_node *root = create_node(NODE_COMMAND, "ls");
	
	t_node *node1 = create_node(NODE_OPERATOR, "|");
	insert_node(&root, node1, OP_PIPE);

	t_node *node2 = create_node(NODE_COMMAND, "grep");
	insert_node(&node1->left, node2, OP_AND);

	print_tree(root, 0);

	delete_node(node);
	delete_node(node1);
	delete_node(node2);
	return (0);
}