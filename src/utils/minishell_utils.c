/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:52:18 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/13 20:59:29 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int gb_present(char *str, t_shell *shell)
{
	t_list *temp;
	t_list *current;

	current = shell->readline_input_to_free;
	while (current)
	{
		temp = current->next;
		if (!ft_memcmp(str, current->content, ft_strlen(str)))
			return(0);
		current = temp;
	}
	return(1);
}

void	free_split(char **split)
{
	int	i;
	t_shell *shell;

	i = 0;
	shell = get_shell();
	while (split[i] != NULL)
	{
		// if (split[i] != NULL && !gb_present(split[i], shell))
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

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return ;
	while (envp[i])
	{
		if (envp[i])
			free(envp[i]);
		i++;
	}
	free(envp);
}
