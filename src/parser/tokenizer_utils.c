/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:54:44 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/15 11:48:49 by brunrodr         ###   ########.fr       */
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

void	toggle_quote(char cmd, t_crop_token *quote)
{
	if (cmd == '\'' && !quote->double_quote)
		quote->single_quote = !quote->single_quote;
	else if (cmd == '\"' && !quote->single_quote)
		quote->double_quote = !quote->double_quote;
}
