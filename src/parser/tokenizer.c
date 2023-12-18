/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:04:14 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/18 09:32:41 by allesson         ###   ########.fr       */
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

	* @var: i: The number of chars that were passed until the delimiter was reached.
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
		while (**cmd != ' ' && **cmd != '\0' && !isdelimiter(*cmd))
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
 * Function: crop_quote_tkn_validator
 * -----------------
 * This is auxiliary function for the crop_quote_tkn function,
 * it helps keep the code clean and organized as it
 * increments i and also modify the string that is being
 * parsed by the function.
 *

	* @param: *i: A pointer to the number of chars that were passed until the delimiter was reached.
 * @param: **cmd: A pointer to the string.
 * @var: quote: The current quote.
 *
 * @return: int.
 */

// int	crop_quote_tkn_validator(int *i, char **cmd)
// {
// 	char quote;
	
// 	quote = **cmd;
// 	if (**cmd == '\'' || **cmd == '"')
// 		quote = **cmd;
// 	else if (!isdelimiter(*cmd) && **cmd && **cmd != 32)
// 	{
// 		while (**cmd && **cmd != 32)
// 		{
// 			(*i)++;
// 			(*cmd)++;
// 		}
// 	}
// 	else
// 		return (false);
// 	(*i)++;
// 	(*cmd)++;
// 	return (true);
// }


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

	* @var: i: The number of chars that were passed until the delimiter was reached.
 * @var: quote: The current quote.
 *
 * @return: int.
 *
 */

int	crop_quote_tkn(char **cmd)
{
	int		i;
	char	quote;
	t_bool	closed;

	i = 1;
	quote = **cmd;
	closed = false;
	(*cmd)++;
	// && **cmd != '<' && **cmd != '>'
	while (**cmd && **cmd != 32)
	{
		while (**cmd != quote && **cmd)
		{
			i++;
			(*cmd)++;
		}
		closed = true;
		i++;
		(*cmd)++;
		if((**cmd == '<' || **cmd == '>') && closed)
			return(i);
		else if(**cmd == '\'' || **cmd == '"')
		{
			quote = **cmd;
			closed = false;
		}
		// if (crop_quote_tkn_validator(&i, cmd) && (**cmd == '\''
		// 		|| **cmd == '"'))
		// 	quote = **cmd;
		// else
		// 	return (i);
		// i++;
		// (*cmd)++;
	}
	// i++;
	// (*cmd)++;
	return (i);
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

	* @var: i: The number of chars that were passed until the delimiter was reached.
 *
 * @return: char *.
 *
 */

char	*crop_tkn(char **cmd, t_hashtable *env)
{
	char	*cropped;
	int		i;

	cropped = *cmd;
	i = 0;
	if (**cmd == '\'' || **cmd == '"')
		i = crop_quote_tkn(cmd);
	else if (isdelimiter(*cmd))
		i = crop_delimiter_tkn(cmd);
	else
	{
		while (**cmd != ' ' && **cmd != '\0' && !isdelimiter(*cmd))
		{
			i++;
			(*cmd)++;
		}
		if (is_expander(**cmd))
			return (append_expanded(cropped, cmd, env, i));
	}
	return (ft_substr(cropped, 0, i));
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

	* @var: *actual_cmd: Will receive the content of the readline stored at g_global variable.
 *
 * @return: void.
 *
 */

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
		handle_token(crop_tkn(&actual_cmd, env));
	}
	expand_all(g_global.tkn_list, env);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_hashtable	*hash;

// 	(void)argc;
// 	(void)argv;
// 	hash = create_hashtable();
// 	init_hash(hash, envp);
// 	prompt(hash);
// }
