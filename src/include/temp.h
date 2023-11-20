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


typedef struct t_line
{
	char *content;
	struct t_line *next;
}	t_line;

/**
 * Data structure: t_files
 * -----------------
 * Is a linked list used to store the files that are found by the wildcard
 * expansion. Basically in file have the name of the file and the next pointer
 * points to the next file. In function 'handle_wildcard' the files are added
 * to the linked list and checked if files and patterns match.
 * 
 * @param: *file: The name of the file.
 * @param: *next: The pointer to the next file.
 * 
 */

// typedef struct s_files
// {
// 	char				*content;
// 	struct s_files		*next;
// }					t_files;

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

// //################################ Wildcard ###################################

// // void    expand_wildcard_and_store(char *pattern);
// void    open_directory(char *pattern);
// t_files *create_file(char *name);
// void add_file(t_files **head, char *name);

#endif