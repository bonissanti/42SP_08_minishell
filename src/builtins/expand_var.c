/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:11:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/31 19:49:53 by brunrodr         ###   ########.fr       */
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

char *handle_elements(t_hashtable *hash_table, char *arg)
{
	char *result[4096];
	t_bool single_quotes;
	t_bool double_quotes;
	int i;
	int j;
	
	i = -1;
	j = -1;
	single_quotes = false;
	double_quotes = false;
	while (arg[++i] != '\0')
	{
		if (arg[i] == '\'')
			single_quotes = !single_quotes;

		
	}
	
}