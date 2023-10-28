/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:46:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/27 16:41:19 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#ifndef AST_H
# define AST_H


typedef enum
{
	NODE_COMMAND,
	NODE_OPERATOR,
	NODE_FILE,
	NODE_REDIRECT,
} t_ast_type;

typedef enum
{
	OP_REDIRECT = 4, 	// <, >, >> 
	OP_PIPE = 3, 		// |
	OP_LOGICAL = 2, 	// &&, ||
	DEFAULT = 0,
} t_operator;

typedef struct s_ast
{
	
	char *args;
	t_operator op;
	t_ast_type type;
	struct s_ast *left;
	struct s_ast *right;
} t_ast;


// typedef enum
// {
// 	OUTFILE = 1,
// 	INFILE = 2,
// 	APPENDOUTFILE = 3,
// 	PARENTHESIS = 3,
// 	LOGICAL_OR = 3,
// 	LOGICAL_AND = 3,
// 	PIPE = 4,
// 	HEREDOC = 5,
// 	COMMAND = 0,
// }	t_height;


#endif