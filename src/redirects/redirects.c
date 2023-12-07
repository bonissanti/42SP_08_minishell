/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:51:04 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 16:03:25 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/segments.h"
#include "../include/exec.h"
#include "../include/hash.h"

void	redirect_input(t_ast *node, char *filename)
{
	if (filename == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	node->fd = open(filename, O_RDONLY);
	if (!verify_file_permissions(filename))
		return ;
}

void	redirect_output(t_ast *node, char *filename)
{
	if (filename == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	node->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!verify_file_permissions(filename))
		return ;
}

void	redirect_append(t_ast *node, char *filename)
{	
	if (filename == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	node->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!verify_file_permissions(filename))
		return ;
}

// void redirect_pipe(int fd_to_redirect, int fd_system)
// {
// 	dup2(fd_to_redirect, fd_system);
// 	close(fd_to_redirect);
// }
