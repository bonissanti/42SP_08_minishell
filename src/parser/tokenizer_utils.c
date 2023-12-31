/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:54:44 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/07 13:18:12 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: is_expander
 * -----------------
 * The is_expander function checks if the char passed to
 * th function is equals to one of the three expanders
 * '$', '*' and '~'.
 * 
 * @param: x: The char to be checked.
 * 
 * @return: int.
 * 
*/

int	is_expander(char x)
{
	if (x == '$' || x == '*' || x == '~')
		return (true);
	return (false);
}

/**
 * Function: append_expanded
 * -----------------
 * The append_expanded function first expands the string
 * then appends it to the cmd_list->args.
 * 
 * @param: *cmd: A pointer to the cmd_list->args.
 * @param: **exp: A pointer to the string to be expanded.
 * @param: *env: A pointer to the hashtable.
 * @param: index: The index of the string to be expanded.
 * @var: *to_expand: A pointer which will receive the substring
 * containing what will be expanded. 
 *
 * @return: char *.
 * 
*/

char	*append_expanded(char *cmd, char **exp, t_hashtable *env, int index)
{
	char	*to_expand;
	char	*test = ft_strdup(*exp);

	to_expand = ft_substr(*exp, 0, crop_delimiter_tkn(&test));
	analyzing_quotes(env, exp);
	return (gnl_strjoin(ft_substr(cmd, 0, index), to_expand));
}

/**
 * Function: expand_all
 * -----------------
 * The expand_all function iterates through the tkn_list
 * and expand all the tokens that are of type WILD or EXPAND
 * before the tkn_list passa through the parser.
 * 
 * @param: *tkn_list: A pointer to the tkn_list.
 * @param: *env: A pointer to the hashtable.
 * @var: *current: A pointer to the current node of the tkn_list.
 * 
 * @return: void.
 * 
*/

void	expand_all(t_tkn_list *tkn_list, t_hashtable *env, t_bool *is_export)
{
	t_tkn_list	*current;

	current = tkn_list;
	(void)is_export;
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

/**
 * Function: handle_token
 * -----------------
 * The handle_token function checks the type which will be
 * assigned to the token based on the first and second
 * char of the *str and then adds it to the tkn_list.
 * 
 * @param: *g_global: A pointer to the global struct.
 * @param: *str: A pointer to the string.
 * 
 * @return: void.
 * 
*/

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

t_bool	has_equal(const char *str, t_bool *is_export)
{
	if (ft_strncmp(g_global.readline_input, "export", 6) != 0)
	{
		*is_export = false;
		return (false);
	}
	while (*str)
	{
		if (*str == '=')
			return (true);
		str++;
	}
	*is_export = false;
	return (false);
}
