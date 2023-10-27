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
} t_node_type;

typedef enum
{
	OP_PIPE,
	OP_AND,
	OP_OR,
	OP_REDIRECT,
	OP_BACKGROUND,
} t_operator;

	



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

typedef struct s_node
{
	
	char *args;
	struct s_node *left;
	struct s_node *right;
	t_node_type type;
} t_node;


#endif