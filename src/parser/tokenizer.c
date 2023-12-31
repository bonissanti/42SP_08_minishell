/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:04:14 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/07 17:29:43 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_global	g_global;

/**
 * Function: crop_delimiter_tkn
 * -----------------
 * The crop_delimiter_tkn function iterates
 * through the string until it finds a delimiter
 * and at the same time counts the number of chars
 * that were passed until the delimiter was reached
 * so it can be returned and used by other functions.
 *
 * @param: **cmd: A pointer to the string.
 * @var: i: The number of chars that were passed until the delimiter 
 * was reached.
 *
 * @return: int.
 *
 */

int	crop_delimiter_tkn(char **cmd)
{
	int	i;

	i = 0;
	if (**cmd == '$' || **cmd == '~' || **cmd == '*')
	{
		i++;
		(*cmd)++;
		while ((**cmd != ' ' && **cmd != '\0' && !isdelimiter(*cmd))
			|| (**cmd == '$'))
		{
			i++;
			(*cmd)++;
		}
	}
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

/**
 * Function: crop_quote_tkn
 * -----------------
 * The crop_quote_tkn function iterates
 * through the string until it finds a delimiter
 * and at the same time counts the number of chars
 * that were passed until the delimiter was reached
 * so it can be returned and used by other functions.
 *
 * @param: **cmd: A pointer to the string.
 * @var: i: The number of chars that were passed until the delimiter was reached
 * @var: quote: The current quote.
 *
 * @return: int.
 *
 */

static int	process_quote(char **cmd, char quote, t_bool *closed)
{
	int	i;

	i = 0;
	if ((**cmd == '<' || **cmd == '>') && closed)
		return (i);
	else if(**cmd == '\'' || **cmd == '"' )
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

int	crop_quote_tkn(char **cmd)
{
	int		i;
	char	quote;
	t_bool	closed;

	i = 1;
	quote = **cmd;
	closed = false;
	while ((**cmd && !closed) || is_expander(**cmd) || (**cmd && closed && **cmd != 32))
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

char	*copy_var_export(char **cmd, t_bool *is_export)
{
	int		i;
	char	*cropped;

	cropped = *cmd;
	i = 0;
	while (**cmd && *is_export && !isdelimiter(*cmd) && **cmd != '$')
	{
		i++;
		(*cmd)++;
	}
	return (ft_substr(cropped, 0, i));
}

/**
 * Function: crop_tkn
 * -----------------
 * The crop_tkn function iterates through the string
 * and generate a substring based on the result of
 * the isdelimiter function or is_expander function.
 *
 * @param: **cmd: A pointer to the string.
 * @param: *env: A pointer to the hashtable.
 * @var: char *cropped: The substring.
 * @var: i: The number of chars that were passed until the delimiter was reached
 *
 * @return: char *.
 *
 */

char	*crop_tkn(char **cmd, t_hashtable *env, t_bool *is_export)
{
	char	*cropped;
	int		i;
	char	quote;
	t_bool	closed;
	(void)is_export;
	(void)env;

	cropped = *cmd;
	closed = false;
	(void)is_export;
	ft_memset(&quote, 0, sizeof(quote));
	i = 0;
	if (**cmd == '\'' || **cmd == '"')
		i = crop_quote_tkn(cmd);
	else if (isdelimiter(*cmd))
		i = crop_delimiter_tkn(cmd);
	else
	{
		while (**cmd != ' ' && **cmd != '\0' && !closed)
		{
			i++;
			(*cmd)++;
			if ((**cmd == '\'' || **cmd == '"'))
			{
				quote = **cmd;
				closed = false;
			}
			else if (**cmd == quote)
				closed = true;
			else if (isdelimiter(*cmd) && closed == true)
				return (ft_substr(cropped, 0, i));
		}
		if (ft_strncmp(cropped, "export", 6) == 0)
			*is_export = true;
	}
	return (ft_strtrim(gb_to_free(ft_substr(cropped, 0, i)), " "));
}

/**
 * Function: tokenizer
 * -----------------
 * The tokenizer function iterates through the readline input
 * and generate a tkn_list based on the result of the crop_tkn function,
 * that is further passed to the expand_all function that finishes the process
 * of tokenization.
 *
 * @param: *g_global: A pointer to the global struct.
 * @param: *cmd: A pointer to the string.
 * @param: *env: A pointer to the hashtable.
 * @var: *actual_cmd: Will receive the content of the readline 
 * stored at g_global variable.
 *
 * @return: void.
 *
 */

void	tokenizer(t_hashtable *env)
{
	char	*actual_cmd;
	t_bool	is_export;

	is_export = false;
	actual_cmd = g_global.readline_input;
	g_global.tkn_list = NULL;
	while (*actual_cmd)
	{
		// if (is_export && has_equal(actual_cmd, &is_export))
		// {
		// 	if (ft_isspace(*actual_cmd))
		// 		skip_spaces(&actual_cmd);
		// 	handle_token(copy_var_export(&actual_cmd, &is_export));
		// 	break ;
		// }
		if (ft_isspace(*actual_cmd))
			skip_spaces(&actual_cmd);
		if (!(*actual_cmd))
			return ;
		handle_token(crop_tkn(&actual_cmd, env, &is_export));
	}
	expand_all(g_global.tkn_list, env, &is_export);
}
