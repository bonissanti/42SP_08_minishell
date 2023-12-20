/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:51:04 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/19 11:57:45 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirect_input(t_ast *node, char *filename)
{
	int		tmp_fd;
	char	*tmp_filename;

	tmp_filename = "/tmp/minishell_tmp_file";
	if (filename == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token EOF\n");
		return (-1);
	}
	node->in_fd = open(filename, O_RDONLY);
	if (node->in_fd == -1 || !verify_file_permissions(filename))
	{
		tmp_fd = open(tmp_filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (tmp_fd != -1)
		{
			close(tmp_fd);
			ft_fprintf(2, "minishell: %s: %s\n", filename, strerror(errno));
			node->in_fd = open(tmp_filename, O_RDONLY);
			unlink(tmp_filename);
			return (0);
		}
	}
	return (0);
}

int	redirect_output(t_ast *node, char *filename)
{
	if (filename == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token EOF\n");
		return (1);
	}
	node->out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!verify_file_permissions(filename))
		return (1);
	return (0);
}

int	redirect_append(t_ast *node, char *filename)
{
	if (filename == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token EOF\n");
		return (1);
	}
	node->out_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!verify_file_permissions(filename))
		return (1);
	return (0);
}
