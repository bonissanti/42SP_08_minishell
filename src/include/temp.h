/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:11:53 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/17 14:29:13 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMP_H
# define TEMP_H

#include "../include/hash.h"
#include "../../libft/libft.h"

typedef struct t_line
{
	char *content;
	struct t_line *next;
}	t_line;

typedef struct s_exec
{
	int in_fd;
	int out_fd;
	int fd_heredoc;
	int cmd_count;
	char **cmd;
	char *delim;
} 	t_exec;


//############################### Init ###################################

t_exec *init_exec(t_exec *exec);
t_line *init_list(t_line *list);
void	handle_heredoc(t_hashtable *env, char *delim);
char *check_expansion(t_hashtable *env, char **line, size_t *len);

#endif