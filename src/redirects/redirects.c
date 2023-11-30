/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:51:04 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/29 17:46:32 by brunrodr         ###   ########.fr       */
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
	node->in_fd = open(filename, O_RDONLY);
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
	node->out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	node->out_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!verify_file_permissions(filename))
		return ;
}
