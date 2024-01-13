/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:54:44 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/12 22:59:15 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_expander(char x)
{
	if (x == '$' || x == '*' || x == '~')
		return (true);
	return (false);
}

void	expand_iterator(char **cmd, int *i)
{
	*i = *i + 1;
	(*cmd)++;
	while ((**cmd != ' ' && **cmd != '\0' && !isdelimiter(*cmd))
		|| (**cmd == '$'))
	{
		*i = *i + 1;
		(*cmd)++;
	}
}

void	handle_token(char *str, t_shell *shell)
{
	if (*str == '(')
		add_tkn_list(new_tkn_list(str, O_PARENTESIS), shell);
	else if (*str == ')')
		add_tkn_list(new_tkn_list(str, C_PARENTESIS), shell);
	else if (!ft_strncmp(str, ">>", 2))
		add_tkn_list(new_tkn_list(str, APPEND), shell);
	else if (*str == '>')
		add_tkn_list(new_tkn_list(str, REDIRECT), shell);
	else if (!ft_strncmp(str, "<<", 2))
		add_tkn_list(new_tkn_list(str, HERE_DOC), shell);
	else if (*str == '<')
		add_tkn_list(new_tkn_list(str, INFILE), shell);
	else if (!ft_strncmp(str, "||", 2))
		add_tkn_list(new_tkn_list(str, OR), shell);
	else if (*str == '|')
		add_tkn_list(new_tkn_list(str, PIPE), shell);
	else if (!ft_strncmp(str, "&&", 2))
		add_tkn_list(new_tkn_list(str, AND), shell);
	else if (*str == '$')
		add_tkn_list(new_tkn_list(str, EXPAND), shell);
	else if (*str == '*' || *str == '~')
		add_tkn_list(new_tkn_list(str, WILD), shell);
	else
		add_tkn_list(new_tkn_list(str, IDENTIFIER), shell);
}

int	process_quote(char **cmd, char quote, t_bool *closed)
{
	int	i;

	i = 0;
	if ((**cmd == '<' || **cmd == '>') && closed)
		return (i);
	else if (**cmd == '\'' || **cmd == '"' )
		(*cmd)++;
	while (**cmd != quote && **cmd)
	{
		i++;
		(*cmd)++;
	}
	if (**cmd == quote)
		*closed = true;
	i++;
	if (**cmd)
		(*cmd)++;
	return (i);
}
