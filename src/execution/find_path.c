/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:08:58 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/13 19:18:01 by aperis-p         ###   ########.fr       */
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
			return (full_path);
		free(full_path);
		temp++;
	}
	free_split(temp_bkp);
	if (result == 127)
		ft_fprintf(2, "minishell: %s: command not found\n", node->cmds);
	else if (result == 126)
		ft_fprintf(2, "minishell: %s: %s\n", node->cmds, strerror(errno));
	return (NULL);
}
