/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:47:48 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/16 20:30:50 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function: is_solo
 * -----------------
 * This is a helper function that evaluates if the current delimiter position is
 * the correct one to the function ast_split, split the string at the correct point.
 * This is needed to avoid problems when spliting a string which may have a
 * sequence of the same delimiter.
 *   
 * @param: c: The string being split.
 * 
 * @var: i: The iterator to track the actual position.
 * @var: left: The char before the current position.
 * @var: right: The char after the current position.
 * 
 * @return: Returns 1 if c is ok to be split, 0 otherwise.
 *
 */

int	is_solo(char *c)
{
	int		i;
	char	left;
	char	right;

	i = 0;
	left = *(c + i - 1);
	right = *(c + i + 1);
	if ((left != 32 && right != 32) || (left != 32 && right == 32))
		return (1);
	else
		return (0);
}

/**
 * Function: is_delimiter
 * -----------------
 * This function verifies if the current *c is equal to the delimiter
 * and return the result to ft_del_count on each iteration.
 *   
 * @param: *c: The string to be compared with the delimiter.
 * @param: delimiter: The delimiter.
 * @param: in_quotes: The state of quotes at the *c position.
 * 
 * @return: Returns 1 if *c is a delimiter, 0 otherwise.
 *
 */

static int	is_delimiter(char *c, char delimiter, t_bool in_quotes)
{
	if (*c == delimiter && !in_quotes)
	{
		if (is_solo(c))
			return (1);
	}
	return (0);
}

/**
 * Function: ft_del_count
 * -----------------
 * A sub-function of ast_split, which counts how many delimiters occurrences the string has.
 *   
 * @param: *s: The string to be analyzed.
 * @param: c: The delimiter.
 * 
 * @var: counter: The total of delimiter occurrences.
 * @var: *ptr: A pointer to save the original s reference.
 * @var: i: An iterator to work with *ptr.
 * @var: in_quotes: The state of quotes at the *s position.
 * 
 * @return: Returns counter, which stores the total of delimiter occorrences.
 *
 */

static size_t	ft_del_count(char *s, char c)
{
	size_t	counter;
	char	*ptr;
	int		i;
	t_bool	in_quotes;

	ptr = s;
	counter = 0;
	i = 0;
	in_quotes = 0;
	while (*(ptr + i))
	{
		while (is_delimiter((ptr + i), c, in_quotes) && *(ptr + i) != '\0')
			i++;
		while (!is_delimiter((ptr + i), c, in_quotes) && *(ptr + i) != '\0')
		{
			if (*(ptr + i) == '\"' || *(ptr + i) == '\'')
				in_quotes = !in_quotes;
			i++;
		}
		if (*(ptr + i) != '\0' || !is_delimiter((ptr + i - 1), c, in_quotes))
			counter++;
	}
	return (counter);
}

/**
 * Function: ft_btw
 * -----------------
 * A sub-function of ast_split, ft_btw counts how many chars
 * *s has between one delimiter and another at the *s current position.
 *   
 * @param: *s: The string to be analyzed.
 * @param: c: The delimiter.
 * 
 * @var: counter: The total of delimiter occurrences.
 * @var: *ptr: A pointer to save the original s reference.
 * @var: i: An iterator to work with *ptr.
 * @var: in_quotes: The state of quotes at the *s position.
 * 
 * @return: Returns counter, which stores the total of delimiter occorrences.
 *
 */

static int	ft_btw(char *s, char c)
{
	int		counter;
	char	*ptr;
	int		i;
	t_bool	in_quotes;

	ptr = s;
	if (is_delimiter((ptr + 0), c, false))
		i = 1;
	else
		i = 0;
	counter = 0;
	in_quotes = false;
	while (*(ptr + i))
	{
		if (is_delimiter((ptr + i), c, in_quotes))
		{
			return (counter);
		}
		if (*(ptr + i) == '\"' || *(ptr + i) == '\'')
			in_quotes = !in_quotes;
		counter++;
		i++;
	}
	return (counter);
}

/**
 * Function: ast_split
 * -----------------
 * This is one of the core functions of the ast creation,
 * it is designed to split the command formed by the parser
 * to be split, to be able to be used by the excve
 * function as a 2d array containing the command and their arguments.
 *   
 * @param: *s: The string to be analyzed.
 * @param: c: The delimiter.
 * 
 * @var: **result: The 2d array containing the command and their arguments.
 * @var: **temp: A helper temp variable.
 * 
 * @return: Returns result, the 2d array.
 *
 */

char	**ast_split(char *s, char c)
{
	char	**result;
	char	**temp;

	result = (char **)ft_calloc(ft_del_count(s, c) + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	temp = result;
	while (*s)
	{
		if (!is_delimiter(s, c, false))
		{
			*temp = ft_calloc((ft_btw(s, c) + 1), sizeof(char));
			if (*temp == NULL)
				return (NULL);
			ft_strlcpy(*temp++, s, ft_btw(s, c) + 1);
			s += ft_btw(s, c);
		}
		else
			s++;
	}
	*temp = NULL;
	return (result);
}
