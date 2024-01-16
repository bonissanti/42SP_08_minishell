/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:39:50 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/15 20:59:57 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
