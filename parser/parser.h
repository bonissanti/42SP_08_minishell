/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:02:11 by aperis-p          #+#    #+#             */
/*   Updated: 2023/10/31 23:33:18 by aperis-p         ###   ########.fr       */
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
	NL,
} t_tkn_type;

typedef struct s_tkn_list{
	t_tkn_type			type;
	char				*content;
	struct s_tkn_list	*next;
	struct s_tkn_lsit	*prev;
} t_tkn_list;

#include "../minishell.h"

void		tokenizer(t_global *global, char *cmd);
void 		skip_spaces(char **str);
int			isdelimiter(char *cmd);
t_tkn_list	*new_tkn_list(char *content, t_tkn_type type);
void		handle_token(t_global *global, char *str);
void		add_tkn_list(t_global *global, t_tkn_list *new_list);
void		print_tkn_list(t_tkn_list *tkn_list);   //DELETE THIS BEFORE DELIVERY 
char		*tkn_type_string(t_tkn_type type);      //DELTE THIS BEFORE DELIVERY


#endif