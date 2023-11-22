/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:51:04 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 12:03:25 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/segments.h"

void	redirect_input(char *filename)
{
	int	file;

	file = open(filename, O_RDONLY);
	if (file < 0)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", filename, strerror(errno));
		return ;
	}
	dup2(file, STDIN_FILENO);
	close(file);
}

void	redirect_output(char *filename)
{
	int file;

	file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", filename, strerror(errno));
		return ;
	}
	dup2(file, STDOUT_FILENO);
	close(file);
}

void	redirect_append(char *filename)
{
	int	file;
	
	file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file < 0)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", filename, strerror(errno));
		return ;
	}
	dup2(file, STDOUT_FILENO);
	close(file);
}