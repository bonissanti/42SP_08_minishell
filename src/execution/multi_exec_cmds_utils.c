/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:35:32 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/14 14:44:00 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_printf_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		ft_fprintf(2, "fd didn't have any lines to print.\n");
		return ;
	}
	while (line)
	{
		ft_fprintf(2, "es: %s", line);
		line = get_next_line(fd);
	}
	ft_fprintf(2, "____________________\n");
}

int	exec_simple(t_hashtable *hash, t_ast *node)
{
	if (!analyze_cmd(hash, node))
		return (g_global.cmd_status);
	if (is_builtin(node))
		execute_builtin(hash, node);
	else
		g_global.cmd_status = execve(node->path, node->args, NULL);
	delete_node(g_global.ast);
	destroy_hashtable(hash);
	free_lists();
	return (g_global.exit_status);
}