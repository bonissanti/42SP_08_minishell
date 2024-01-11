/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:04:14 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/10 21:34:17 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_global	g_global;

int	crop_delimiter_tkn(char **cmd)
{
	int	i;

	i = 0;
	if (**cmd == '$' || **cmd == '~' || **cmd == '*')
		expand_iterator(cmd, &i);
	else if (!ft_strncmp(*cmd, "||", 2) || !ft_strncmp(*cmd, "&&", 2)
		|| !ft_strncmp(*cmd, "<<", 2) || !ft_strncmp(*cmd, ">>", 2))
	{
		i = 2;
		(*cmd) += 2;
	}
	else
	{
		i++;
		(*cmd)++;
	}
	return (i);
}

int	crop_quote_tkn(char **cmd)
{
	int		i;
	char	quote;
	t_bool	closed;

	i = 1;
	quote = **cmd;
	closed = false;
	while ((**cmd && !closed) || is_expander(**cmd)
		|| (**cmd && closed && **cmd != 32))
	{
		i += process_quote(cmd, quote, &closed);
		if (!(**cmd))
			return (i);
		else if ((**cmd == '<' || **cmd == '>') && closed)
			return (i);
		else if (**cmd == '\'' || **cmd == '"')
		{
			quote = **cmd;
			closed = false;
		}
	}
	return (i);
}

char	*crop_general_tkn(char **cmd, t_bool *closed, int *i, char *quote)
{
	char	*cropped;
	t_bool	past_quote;

	cropped = *cmd;
	past_quote = false;
	while ((**cmd != ' ' && **cmd != '\0' && !(*closed))
		|| ((past_quote && **cmd != '\0' && !(*closed))))
	{
		*i = *i + 1;
		(*cmd)++;
		if ((**cmd == '\'' || **cmd == '"'))
		{
			*quote = **cmd;
			*closed = false;
			past_quote = true;
		}
		else if (**cmd == *quote)
		{
			*closed = true;
			past_quote = false;
		}
		else if (isdelimiter(*cmd) && *closed == true)
			return (ft_substr(cropped, 0, *i));
	}
	return (NULL);
}

char	*crop_tkn(char **cmd)
{
	char	*cropped;
	int		i;
	char	quote;
	t_bool	closed;
	char	*general;

	cropped = *cmd;
	closed = false;
	ft_memset(&quote, 0, sizeof(quote));
	i = 0;
	if (**cmd == '\'' || **cmd == '"')
		i = crop_quote_tkn(cmd);
	else if (isdelimiter(*cmd))
		i = crop_delimiter_tkn(cmd);
	else
	{
		general = crop_general_tkn(cmd, &closed, &i, &quote);
		if (general)
			return (general);
	}
	return (ft_strtrim(gb_to_free(ft_substr(cropped, 0, i)), " "));
}

void	tokenizer(t_hashtable *env)
{
	char	*actual_cmd;

	actual_cmd = g_global.readline_input;
	g_global.tkn_list = NULL;
	while (*actual_cmd)
	{
		if (ft_isspace(*actual_cmd))
			skip_spaces(&actual_cmd);
		if (!(*actual_cmd))
			return ;
		handle_token(crop_tkn(&actual_cmd));
	}
	expand_all(g_global.tkn_list, env);
}
