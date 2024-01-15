/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:51:36 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/15 11:41:04 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		get_dir_and_token(t_file *file, char *pattern, t_shell *shell);
static t_bool	wildcard_match(char *file, char *pattern);

inline void	finish_wildcard(t_segment *head, t_file *file, char **args)
{
	if (!head)
	{
		closedir(file->dir);
		safe_free((void **)&file);
		return ;
	}
	*args = generate_results(head);
	free_segments(head);
	closedir(file->dir);
	safe_free((void **)&file);
}

char	*generate_results(t_segment *segments)
{
	static char	result[4096];
	int			pos;

	pos = 0;
	result[0] = '\0';
	while (segments)
	{
		if (pos != 0)
		{
			ft_strncat(result, " ", 4096 - pos - 1);
			pos += 1;
		}
		ft_strncat(result, segments->str, 4096 - pos - 1);
		pos += ft_strlen(segments->str);
		segments = segments->next;
	}
	return (result);
}

void	handle_wildcard(char **args, t_shell *shell)
{
	t_file		*file;
	t_segment	*head;

	head = NULL;
	file = ft_calloc(1, sizeof(t_file));
	init_structs(file, 0, sizeof(t_file));
	get_dir_and_token(file, *args, shell);
	file->dir = opendir(file->directory);
	if (!file->dir)
	{
		ft_fprintf(2, "Error: %s\n", strerror(errno));
		return ;
	}
	file->entry = readdir(file->dir);
	while (file->entry)
	{
		stat(file->entry->d_name, &file->entry_stat);
		if (ft_strncmp(file->entry->d_name, ".", 1) != 0
			&& ft_strncmp(file->entry->d_name, "..", 2) != 0
			&& wildcard_match(file->entry->d_name, file->token))
			add_segments(&head, file->entry->d_name);
		file->entry = readdir(file->dir);
	}
	finish_wildcard(head, file, args);
}

static void	get_dir_and_token(t_file *file, char *pattern, t_shell *shell)
{
	char	*temp_token;
	char	temp_dir[1000];
	size_t	len;

	temp_token = ft_strtok(pattern, "/");
	ft_memset(temp_dir, 0, 1000);
	if (*pattern == '*')
		temp_dir[0] = '.';
	while (temp_token)
	{
		ft_strcat(temp_dir, temp_token);
		if (temp_token && !ft_strchr(temp_token, '*'))
			ft_strcat(temp_dir, "/");
		file->token = temp_token;
		temp_token = ft_strtok(NULL, "/");
	}
	len = ft_strcspn(temp_dir, "*");
	file->directory = gb_to_free(ft_strndup(temp_dir, len), shell);
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
		if (*file != '\0' && *pattern == *file)
			return (wildcard_match(file + 1, pattern + 1));
		file++;
	}
	if (*pattern == '*' && *(pattern + 1) == '\0')
		return (true);
	return (false);
}
