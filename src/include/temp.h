/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:11:53 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/16 18:08:07 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMP_H
# define TEMP_H

#include "../include/hash.h"
#include "../../libft/libft.h"

typedef struct s_exec
{
	int in_fd;
	int out_fd;
	int fd_heredoc;
	int cmd_count;
	char **cmd;
	char *delim;
} 	t_exec;

#endif