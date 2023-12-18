/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:51:04 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/11 14:43:46 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void redirect_input(t_ast *node, char *filename)
{
    int tmp_fd;
    char *tmp_filename = "/tmp/minishell_tmp_file";

    if (filename == NULL)
    {
        ft_fprintf(2, "minishell: syntax error near unexpected token EOF\n");
        return ;
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
        }
    }
}

void	redirect_output(t_ast *node, char *filename)
{
	if (filename == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token EOF\n");
		return ;
	}
	node->out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!verify_file_permissions(filename))
		return ;
}

void	redirect_append(t_ast *node, char *filename)
{
	if (filename == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token EOF\n");
		return ;
	}
	node->out_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!verify_file_permissions(filename))
		return ;
}
