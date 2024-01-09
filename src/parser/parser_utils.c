/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:39:50 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/08 19:15:54 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

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

int	is_operator(t_tkn_type tkn)
{
	if (tkn == PIPE || tkn == AND || tkn == OR)
		return (true);
	return (false);
}

int	is_redirect(t_tkn_type tkn)
{
	if (tkn == INFILE || tkn == REDIRECT || tkn == HERE_DOC || tkn == APPEND)
		return (true);
	return (false);
}
