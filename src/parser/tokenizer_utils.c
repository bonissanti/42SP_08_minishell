/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:54:44 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/08 18:24:14 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_expander(char x)
{
	if (x == '$' || x == '*' || x == '~')
		return (true);
	return (false);
}

char	*append_expanded(char *cmd, char **exp, t_hashtable *env, int index)
{
	char	*to_expand;
	char	*test = ft_strdup(*exp);

	to_expand = ft_substr(*exp, 0, crop_delimiter_tkn(&test));
	analyzing_quotes(env, exp);
	return (gnl_strjoin(ft_substr(cmd, 0, index), to_expand));
}

void	expand_all(t_tkn_list *tkn_list, t_hashtable *env)
{
	t_tkn_list	*current;

	current = tkn_list;
	while (current)
	{
		if (current->type == EXPAND || current->type == WILD
			|| current->type == IDENTIFIER)
		{
			if ((*current->content == '$' || *current->content == '\\'
					|| *current->content == '\'' || *current->content == '"'
					|| current->type == IDENTIFIER))
				analyzing_quotes(env, &current->content);
			if (*current->content == '~')
				expand_tilde(env, current->content);
			else if (*current->content == '*')
				handle_wildcard(&current->content);
		}
		current = current->next;
	}
}

void	handle_token(char *str)
{
	if (*str == '(')
		add_tkn_list(new_tkn_list(str, O_PARENTESIS));
	else if (*str == ')')
		add_tkn_list(new_tkn_list(str, C_PARENTESIS));
	else if (!ft_strncmp(str, ">>", 2))
		add_tkn_list(new_tkn_list(str, APPEND));
	else if (*str == '>')
		add_tkn_list(new_tkn_list(str, REDIRECT));
	else if (!ft_strncmp(str, "<<", 2))
		add_tkn_list(new_tkn_list(str, HERE_DOC));
	else if (*str == '<')
		add_tkn_list(new_tkn_list(str, INFILE));
	else if (!ft_strncmp(str, "||", 2))
		add_tkn_list(new_tkn_list(str, OR));
	else if (*str == '|')
		add_tkn_list(new_tkn_list(str, PIPE));
	else if (!ft_strncmp(str, "&&", 2))
		add_tkn_list(new_tkn_list(str, AND));
	else if (*str == '$')
		add_tkn_list(new_tkn_list(str, EXPAND));
	else if (*str == '*' || *str == '~')
		add_tkn_list(new_tkn_list(str, WILD));
	else
		add_tkn_list(new_tkn_list(str, IDENTIFIER));
}
