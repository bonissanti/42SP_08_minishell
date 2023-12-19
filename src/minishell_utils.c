/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:52:18 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/19 11:54:03 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	init_structs(void *structs, int type, size_t struct_size)
{
	ft_memset(structs, type, struct_size);
}

int	ft_count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		if (split[i] != NULL)
		{
			free(split[i]);
			split[i] = NULL;
		}
		i++;
	}
	if (split != NULL)
	{
		free(split);
		split = NULL;
	}
}

void	safe_free(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
