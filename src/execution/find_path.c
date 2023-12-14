/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:08:58 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/05 17:30:32 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/segments.h"

char	*build_cmd_path(t_ast *node, char *path)
{
	char	**temp;
	char	*full_path;
	char	*slash;
	int		result;

	temp = ft_split(path, ':');
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
	free_split(temp);
	if (result == 126)
		ft_fprintf(2, "minishell: %s: command not found\n", node->cmds);
	else if (result == 127)
		ft_fprintf(2, "minishell: %s: %s\n", node->cmds, strerror(errno));
	return (NULL);
}