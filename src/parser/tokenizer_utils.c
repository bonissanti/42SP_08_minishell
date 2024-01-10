/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:54:44 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/10 15:56:43 by aperis-p         ###   ########.fr       */
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

void	expand_all(t_tkn_list *tkn_list, t_hashtable *env)
{
	t_tkn_list	*current;

	current = tkn_list;
	while (current)
	{
		if (current->type == EXPAND || current->type == WILD
			|| (current->type == IDENTIFIER))
		{			
			if ((*current->content == '$' || *current->content == '\\' 
				|| *current->content == '\'' || *current->content == '"' 
				|| current->type == IDENTIFIER) 
				&& (current->prev && ft_strcmp(current->prev->content, "export")))
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
