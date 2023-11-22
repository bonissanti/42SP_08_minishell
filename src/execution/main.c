/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:04:20 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 18:05:42 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/temp_ast.h"

int main(void)
{
	t_temp_ast *root = NULL;

	t_temp_ast *node1 = create_node(TYPE_COMMAND, "ls", OP_REDIRECT);
	insert_temp_ast(&root, node1);

	t_temp_ast *node2 = create_node(TYPE_OPERATOR, ">", OP_REDIRECT);
	insert_temp_ast(&root, node2);

	t_temp_ast *node3 = create_node(TYPE_FILE, "outfile.txt", DEFAULT);
	insert_temp_ast(&root, node3);
}
