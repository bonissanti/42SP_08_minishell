/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:02:11 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/08 21:59:41 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum {
	IDENTIFIER,
	INFILE,
	REDIRECT,
	HERE_DOC,
	APPEND,
	PIPE,
	O_PARENTESIS,
	C_PARENTESIS,
	AND,
	OR,
	EXPAND,
	WILD
} t_tkn_type;

typedef enum 
{
	TYPE_COMMAND,
	TYPE_OPERATOR,
	TYPE_FILE,
	TYPE_REDIRECT,
} t_type;

typedef enum
{
	OP_REDIRECT = 2, 	// <, >, >> 
	OP_PIPE = 3, 		// |
	OP_LOGICAL = 4, 	// &&, ||
	DEFAULT = 0,
} t_operator;

typedef struct s_cmd_list
{    
    t_type 	type;
    char *args;
    t_operator	prec_weight;
    char *infile;
    char *outfile;
	e_bool here_doc;
	struct s_cmd_list	*next;
	struct s_cmd_lsit	*prev;
} t_cmd_list;

typedef struct s_tkn_list {
	t_tkn_type			type;
	char				*content;
	struct s_tkn_list	*next;
	struct s_tkn_lsit	*prev;
} t_tkn_list;

#include "../minishell.h"


void		tokenizer(t_global *g_global, char *cmd);
void 		skip_spaces(char **str);
int			isdelimiter(char *cmd);
t_tkn_list	*new_tkn_list(char *content, t_tkn_type type);
void		handle_token(t_global *g_global, char *str);
t_tkn_list	*last_tkn_list(t_tkn_list *tkn_list);
void		add_tkn_list(t_global *g_global, t_tkn_list *new_list);
void		print_tkn_list(t_tkn_list *tkn_list);   //DELETE THIS BEFORE DELIVERY 
char		*tkn_type_string(t_tkn_type type);      //DELETE THIS BEFORE DELIVERY
t_tkn_list	*parser(t_global *g_global);
int			command_consistency(t_tkn_list *tokenized);

#endif