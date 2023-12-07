/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:46:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 17:48:25 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include <stdio.h>
#include <stdlib.h>
#include "../../libft/libft.h"
// #include "exec.h"

typedef enum
{
	TYPE_COMMAND,
	TYPE_OPERATOR,
	TYPE_REDIRECT,
}	t_type;

typedef enum
{
	OP_REDIRECT = 3,
	OP_HEREDOC = 4,
	OP_PIPE = 3,  
	OP_LOGICAL = 3,
	DEFAULT = 0,
}	t_op;

typedef struct s_exec
{
	int	in_fd;
	int	out_fd;
	int old_stdin;
	int old_stdout;
	int pipes_count;
	int count_pipes;
}	t_exec;

typedef struct s_ast
{
	
	char *cmds;
	char **args;
	// char **split; //
	char *path;
	char *delim;
	int exit_status;
	int	in_fd;
	int	out_fd;
	t_op weight;
	t_type type;
	pid_t pid;
	struct s_ast *left;
	struct s_ast *right;
} 	t_ast;


//############################### AST #########################################

t_ast 				*create_node(t_type type, char *cmds, t_op weight);
void 				insert_ast(t_ast **head, t_ast *new_node, t_exec *exec);
void				delete_node(t_ast *head);
void				pre_order_traversal(t_ast *head); // Remover depois

//############################### UTILS #######################################

char	**ast_split(char const *s, char c);

#endif