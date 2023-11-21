/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:46:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/21 18:44:21 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#ifndef AST_H
# define AST_H


typedef enum 
{
	TYPE_COMMAND,
	TYPE_OPERATOR,
	TYPE_FILE,
	TYPE_REDIRECT,
} t_type;

// Executa de baixo pra cima, da menor precedencia ao de maior precedencia
typedef enum
{
	OP_REDIRECT = 2, 	// <, >, >> 
	OP_PIPE = 3, 		// |
	OP_LOGICAL = 3, 	// &&, ||
	DEFAULT = 0,
} t_operator;

typedef struct s_ast
{
	
	char *args;
	char **path;
	t_operator op;
	t_type type;
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