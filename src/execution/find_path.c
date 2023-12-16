/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:08:58 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/14 17:37:55 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*build_cmd_path(t_ast *node, char *path)
{
	char	**temp;
	char	**temp_bkp;
	char	*full_path;
	char	*slash;
	int		result;

	temp = ft_split(path, ':');
	temp_bkp = temp;
	while (*temp)
	{
		slash = ft_strjoin(*temp, "/");
		full_path = ft_strjoin(slash, node->cmds);
		free(slash);
		result = verify_cmd_permissions(full_path);
		if (result == 0)
		{
			free_split(temp_bkp);
			return (full_path);
		}
		free(full_path);
		temp++;
	}
	free_split(temp_bkp);
	return (NULL);
}
