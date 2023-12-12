/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:35:32 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/11 14:43:47 by aperis-p         ###   ########.fr       */
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
