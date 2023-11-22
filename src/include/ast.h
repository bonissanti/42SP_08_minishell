/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:46:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 17:43:41 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#ifndef AST_H
# define AST_H

typedef enum
{
	TYPE_COMMAND,
	TYPE_OPERATOR,
	TYPE_FILE,
	TYPE_REDIRECT,
}					t_type;

// Inverted order of precedence
typedef enum
{
	OP_REDIRECT = 2, // <, >, >>
	OP_PIPE = 3,     // |
	OP_LOGICAL = 3,  // &&, ||
	DEFAULT = 0,
}					t_operator;

typedef struct s_ast
{
	char			*args;
	char			**path;
	t_operator		op;
	t_type			type;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

//############################### AST #########################################

t_ast				*create_node(t_type type, char *args, t_operator op);
void				insert_ast(t_ast **root, t_ast *new_node);
void				delete_node(t_ast *root);
void				pre_order_traversal(t_ast *root); // Remover depois


#endif