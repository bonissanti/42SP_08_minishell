/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:11:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/01 19:30:44 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char *expand_variable(t_hashtable *hash_table, char *arg)
{
	t_hash *hash;
	
	if (arg[0] == '$')
	{
		hash = search(hash_table, arg + 1);
		if (hash != NULL)
			return (hash->value);
	}
	return (arg);
}

char *remove_quotes(char *arg, char quote)
{
	char result[4096];
	int i;
	int j;

	i = -1;
	j = -1;
	while (arg[++i] != '\0')
	{
		if (arg[i] != quote)
			result[++j] = arg[i];		
	}
	result[++j] = '\0';
	return (ft_strdup(result));
}

char *handle_elements(t_hashtable *hash_table, char *arg)
{
	t_bool single_quotes;
	char result[4096];
	char *expanded;
	int i;
	int j;

	i = 0;
	j = 0;
	single_quotes = false;
	if (arg[0] == '\'' || arg[0] == '\"')
		arg = remove_quotes(arg, arg[0]);
	
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'')
			single_quotes = !single_quotes;
			
		if (arg[i] == '$' && !single_quotes)
		{
			expanded = expand_variable(hash_table, arg + i);
			strcpy(result + j, expanded);
			j += strlen(expanded);
			i += strlen(expanded) - 1;
		}
		else
			result[j++] = arg[i++];
	}
	result[j] = '\0';
	return (ft_strdup(result));
}