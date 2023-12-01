/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:39:50 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/15 23:24:43 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *tkn_type_converter(t_tkn_type type)
{
	if(type == INFILE)
		return ("<");
	else if(type == REDIRECT)
		return (">");
	else if(type == HERE_DOC)
		return ("<<");
	else if (type == APPEND)
		return (">>");
	else if(type == O_PARENTESIS)
		return ("(");
	else if(type == C_PARENTESIS)
		return (")");
	else if(type == AND)
		return ("&&");
	else if(type == OR)
		return ("||");
	else
		return ("|");
}

void	skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}
int isdelimiter(char *cmd)
{
	if(*cmd == '(' || *cmd == ')' || !ft_strncmp(cmd, "||", 2)
	|| *cmd == '|' || !ft_strncmp(cmd, "&&", 2) || !ft_strncmp(cmd, "<<", 2)
	|| *cmd == '<' || !ft_strncmp(cmd, ">>", 2) || *cmd == '>' || *cmd == '*'
	|| *cmd == '~' || *cmd == '$')
		return(1);
	return(0);
}

int is_operator(t_tkn_type tkn)
{
	if(tkn == PIPE || tkn == AND || tkn == OR)
		return (true);
	return (false);
}

int handle_redirect(t_tkn_type tkn)
{
	if(tkn == INFILE || tkn == REDIRECT
	|| tkn == HERE_DOC || tkn == APPEND)
		return (true);
	return (false);
}

