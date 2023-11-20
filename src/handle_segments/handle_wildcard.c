/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:51:36 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/14 17:27:01 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"
#include "../include/temp.h"
#include "../include/segments.h"
#include <errno.h>

static t_bool	wildcard_match(char *str, char *pattern);

// void			handle_wildcard(t_segment **head, char *pattern)
// {
// 	t_segment *current;

// 	current = *head;
// 	while (current)
// 	{
// 		if (wildcard_match(current->str, pattern))
// 			add_segments(head, current->str);
// 		current = current->next;
// 	}
// }

void	handle_wildcard(char *pattern)
{
	t_file *file;
	t_segment *head;
	char *last_token;
	char *token;
	char directory[1000] = {0};

	token = strtok(pattern, "/");

	while (token)
	{
		if (ft_strchr(token, '*' || ft_strchr(token, '?')))
			break ;
		strcat(directory, token);
		if (token && !ft_strchr(token, '*') && !ft_strchr(token, '?'))
			strcat(directory, "/");
		last_token = token;
		token = strtok(NULL, "/");
	}
	head = NULL;
	file = malloc(sizeof(t_file));
	init_structs(file, sizeof(t_file));
	file->dir = opendir("/home/bruno/Documents/42SP/07. Minishell/v atual/42SP_08_minishell/src/ast");
	if (!file->dir)
	{
		printf("Error: %s\n", strerror(errno));
		printf("Error: %s\n", directory);
		return ;
	}

	file->entry = readdir(file->dir);
	while (file->entry)
	{
		stat(file->entry->d_name, &file->entry_stat);
		if (wildcard_match(file->entry->d_name, last_token))
			add_segments(&head, file->entry->d_name);
		file->entry = readdir(file->dir);
	}
	for (t_segment *tmp = head; tmp; tmp = tmp->next)
		printf("%s\n", head->str);
	closedir(file->dir);
}

static t_bool	wildcard_match(char *file, char *pattern)
{
	if (*pattern == '\0')
		return (*file == '\0');

	while (*file)
	{
		if (*pattern == '*')
		{
			if (wildcard_match(file, pattern + 1))
				return (true);
			if (*file && wildcard_match(file + 1, pattern))
				return (true);
			return (false);
		}
		if (*file != '\0' && (*pattern == '?' || *pattern == *file))
			return (wildcard_match(file + 1, pattern + 1));
		file++;
	}
	return (false);
}

	// if (*pattern == '*')
	// {
	// 	if (wildcard_match(file, pattern + 1))
	// 		return (true);
	// 	if (*file && wildcard_match(file + 1, pattern))
	// 		return (true);
	// 	return (false);
	// }
	// if (*file != '\0' && (*pattern == '?' || *pattern == *file))
	// 	return (wildcard_match(file + 1, pattern + 1));
	// return (false);
