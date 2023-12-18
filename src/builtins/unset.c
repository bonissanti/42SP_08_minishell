/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:53:13 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 19:55:25 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if ((!arg || !ft_isalpha(arg[0])) && (arg[0] != '_'))
		return (false);
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
	}
	return (true);
}

void	ft_unset(t_hashtable *hash_table, char **args)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
		return ;
	else
	{
		while (args[++i] != NULL)
		{
			if (is_valid_identifier(args[i]))
				delete_hash(hash_table, args[i]);
			else
				ft_fprintf(2, "minishell: unset: `%s': not a \
					valid identifier\n", args[i]);
		}
	}
	g_global.cmd_status = 0;
}
