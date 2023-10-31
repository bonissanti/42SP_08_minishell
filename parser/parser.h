/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:02:11 by aperis-p          #+#    #+#             */
/*   Updated: 2023/10/30 18:38:18 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char 		*skip_spaces(char *str);
t_tkn_list	*new_tkn_list(char *content, t_tkn_type type);
