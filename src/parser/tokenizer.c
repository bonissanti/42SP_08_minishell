/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:04:14 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/15 12:29:09 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	write_token(char **cmd, int *i, t_crop_token *quote)
{
	if ((quote->double_quote || quote->single_quote) || (!quote->double_quote
			|| !quote->single_quote))
	{
		*i = *i + 1;
		(*cmd)++;
	}
}

static char	*result_token(char **cmd, int *i, char *cropped,
		t_crop_token *quote)
{
	if (isdelimiter(*cmd) && **cmd != '$' && !quote->double_quote
		&& !quote->single_quote)
		return (ft_substr(cropped, 0, *i));
	else if (**cmd == 32 && !quote->double_quote && !quote->single_quote)
		return (ft_substr(cropped, 0, *i));
	return (NULL);
}

char	*crop_general_tkn(char **cmd, int *i, t_crop_token *quote)
{
	char	*cropped;
	char	*result;

	cropped = *cmd;
	while (**cmd != '\0')
	{
		if ((**cmd == '\'' && !quote->double_quote) || (**cmd == '\"'
				&& !quote->single_quote))
		{
			toggle_quote(**cmd, quote);
			if (((!quote->double_quote && **cmd == '\"')
					|| (!quote->single_quote && **cmd == '\'')))
			{
				*i = *i + 1;
				(*cmd)++;
				if (**cmd != '$' || **cmd == 32)
					return (ft_substr(cropped, 0, *i));
			}
		}
		result = result_token(cmd, i, cropped, quote);
		if (result)
			return (result);
		write_token(cmd, i, quote);
	}
	return (NULL);
}

char	*crop_tkn(char **cmd, t_shell *shell)
{
	char			*cropped;
	int				i;
	t_crop_token	quote;
	char			*general;

	cropped = *cmd;
	ft_memset(&quote, 0, sizeof(quote));
	i = 0;
	if (isdelimiter(*cmd))
		i = crop_delimiter_tkn(cmd);
	else
	{
		general = crop_general_tkn(cmd, &i, &quote);
		if (general)
			return (general);
	}
	return (ft_strtrim(gb_to_free(ft_substr(cropped, 0, i), shell), " "));
}

void	tokenizer(t_shell *shell)
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
}
