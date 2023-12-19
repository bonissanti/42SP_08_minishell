/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_and_restore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:01:20 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/19 12:01:22 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	backup_fd(int *old_stdin, int *old_stdout)
{
	*old_stdin = dup(STDIN_FILENO);
	*old_stdout = dup(STDOUT_FILENO);
}

void	restore_fd(int reset_stdin, int reset_stdout)
{
	dup2(reset_stdin, STDIN_FILENO);
	dup2(reset_stdout, STDOUT_FILENO);
	close(reset_stdin);
	close(reset_stdout);
}
