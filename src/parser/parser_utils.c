/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:39:50 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/28 19:13:34 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: tkn_type_converter
 * -----------------
 * The tkn_type_converter function converts a t_tkn_type enum
 * into a string corresponding to the tkn_type.
 * 
 * @param: type: The t_tkn_type enum.
 * 
 * @return: char *.
 * 
*/

char	*tkn_type_converter(t_tkn_type type)
{
	if (type == INFILE)
		return ("<");
	else if (type == REDIRECT)
		return (">");
	else if (type == HERE_DOC)
		return ("<<");
	else if (type == APPEND)
		return (">>");
	else if (type == O_PARENTESIS)
		return ("(");
	else if (type == C_PARENTESIS)
		return (")");
	else if (type == AND)
		return ("&&");
	else if (type == OR)
		return ("||");
	else
		return ("|");
}

/**
 * Function: skip_spaces
 * -----------------
 * The skip_spaces function skips all the spaces found
 * by the function ft_isspace at the beggining of the string.
 * 
 * @param: **str: A pointer to the string.
 * 
 * @return: void.
 * 
*/

void	skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

/**
 * Function: isdelimiter
 * -----------------
 * The isdelimiter function checks if the given char is a delimiter.
 * 
 * @param: *cmd: A pointer to the string.
 * 
 * @return: int.
 * 
*/
int	isdelimiter(char *cmd)
{
	if (*cmd == '(' || *cmd == ')' || !ft_strncmp(cmd, "||", 2) || *cmd == '|'
		|| !ft_strncmp(cmd, "&&", 2) || !ft_strncmp(cmd, "<<", 2) || *cmd == '<'
		|| !ft_strncmp(cmd, ">>", 2) || *cmd == '>' || *cmd == '*'
		|| *cmd == '~' || *cmd == '$')
		return (1);
	return (0);
}

int	is_redirect_op(char *cmd)
{
	if (!ft_strncmp(cmd, "<<", 2) || *cmd == '<' || !ft_strncmp(cmd, ">>", 2)
		|| *cmd == '>')
		return (1);
	return (0);
}

/**
 * Function: is_operator
 * -----------------
 * The is_operator function checks if the given t_tkn_type is an operator.
 * 
 * @param: tkn: The t_tkn_type enum.
 * 
 * @return: int.
 * 
*/

int	is_operator(t_tkn_type tkn)
{
	if (tkn == PIPE || tkn == AND || tkn == OR)
		return (true);
	return (false);
}

/**
 * Function: is_redirect
 * -----------------
 * The is_redirect function checks if the given t_tkn_type is a redirect.
 * 
 * @param: tkn: The t_tkn_type enum.
 * 
 * @return: int.
 * 
*/

int	is_redirect(t_tkn_type tkn)
{
	if (tkn == INFILE || tkn == REDIRECT || tkn == HERE_DOC || tkn == APPEND)
		return (true);
	return (false);
}
