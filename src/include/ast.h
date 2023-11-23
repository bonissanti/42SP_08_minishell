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

#ifndef AST_H
# define AST_H

#include <stdio.h>
#include <stdlib.h>
#include "../../libft/libft.h"

typedef enum
{
	TYPE_COMMAND,
	TYPE_OPERATOR,
	TYPE_FILE,
	TYPE_REDIRECT,
	TYPE_DELIMITER,
}	t_type;

// Inverted order of precedence
typedef enum
{
	OP_REDIRECT = 2, // <, >, >>
	OP_PIPE = 3,     // |
	OP_LOGICAL = 3,  // &&, ||
	DEFAULT = 0,
}	t_op;

typedef struct s_cmd_list
{
	char *args;
	char *infile;
	char *outfile;
	t_bool here_doc;
	struct s_cmd_list *next;
	struct s_cmd_list *prev;
}	t_cmd_list;

typedef struct s_ast
{
	
	char *cmds;
	char **args;
	char *path;
	int in_fd;
	int out_fd;
	char *delim;
	t_op weight;
	t_type type;
	struct s_ast *left;
	struct s_ast *right;
} 	t_ast;

// typedef struct s_ast
// {
// 	char			*args;
// 	char			**path;
// 	t_op			weight;
// 	t_type			type;
// 	struct s_ast	*left;
// 	struct s_ast	*right;
// }					t_ast;

//############################### AST #########################################

t_ast 				*create_node(t_type type, char *args, t_op weight, char *delim);
void				insert_ast(t_ast **root, t_ast *new_node);
void				delete_node(t_ast *root);
void				pre_order_traversal(t_ast *root); // Remover depois

//############################### UTILS #######################################

char	**ast_split(char const *s, char c);

#endif