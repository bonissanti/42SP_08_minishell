/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:46:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/14 14:47:58 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "./minishell.h"

typedef enum
{
	TYPE_COMMAND,
	TYPE_LOGICAL,
	TYPE_PIPE,
	TYPE_REDIRECT,
	TYPE_HEREDOC,
}	t_type;

typedef enum
{
	OP_REDIRECT = 3,
	OP_HEREDOC = 3,
	OP_PIPE = 3,  
	OP_LOGICAL = 3,
	DEFAULT = 0,
}	t_op;

typedef struct s_exec
{
	int prev[2];
	int next[2];
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
	char *path;
	char *delim;
	int num_status;
	int	in_fd;
	int	out_fd;
	t_op weight;
	t_type type;
	pid_t pid;
	t_bool print_hdoc;
	t_bool print_redir;
	t_bool is_freed;
	struct s_ast *left;
	struct s_ast *right;
} 	t_ast;


//############################### AST #########################################

t_ast 				*create_node(t_cmd_list *cmd_list, t_hashtable *env);
void 				insert_ast(t_ast **head, t_ast *new_node, t_exec *exec);
void				delete_node(t_ast *head);
void				pre_order_traversal(t_ast *head); // Remover depois
t_ast				*init_ast(t_cmd_list *cmd_list, t_exec *exec, t_hashtable *env);

//############################### UTILS #######################################

char	**ast_split(char const *s, char c);

#endif