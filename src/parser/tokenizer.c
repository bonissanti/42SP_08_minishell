/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:04:14 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/10 19:52:22 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	cropped = *cmd;
	while (**cmd != ' ' && **cmd != '\0' && !(*closed))
	{
		*i = *i + 1;
		(*cmd)++;
		if ((**cmd == '\'' || **cmd == '"'))
		{
			*quote = **cmd;
			*closed = false;
		}
		else if (**cmd == *quote)
			*closed = true;
		else if (isdelimiter(*cmd) && *closed == true)
			return (ft_substr(cropped, 0, *i));
	}
	return (NULL);
}

char	*crop_tkn(char **cmd, t_shell *shell)
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
	return (ft_strtrim(gb_to_free(ft_substr(cropped, 0, i), shell), " "));
}

void	tokenizer(t_hashtable *env, t_shell *shell)
{
	char	*actual_cmd;

	actual_cmd = shell->readline_input;
	shell->tkn_list = NULL;
	while (*actual_cmd)
	{
		if (ft_isspace(*actual_cmd))
			skip_spaces(&actual_cmd);
		if (!(*actual_cmd))
			return ;
		handle_token(crop_tkn(&actual_cmd, shell), shell);
	}
	expand_all(shell, env);
}
