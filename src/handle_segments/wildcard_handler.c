/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:51:36 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/29 01:26:38 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		get_dir_and_token(t_file *file, char *pattern);
static t_bool	wildcard_match(char *file, char *pattern);

/**
 * Function: finish_wildcard
 * -----------------
 * This is a function that finishes the wildcard expansion. It will print
 * the files that match with the token. Then it will free the linked list
 * and the structure.
 *   
 * @param: *head: The head of the linked list.
 * @param: *file: The structure that contains the directory, token, etc.
 * @var: *tmp: The temporary pointer to the linked list.
 * 
 * @return: void
 * 
 */

inline void	finish_wildcard(t_segment *head, t_file *file, char **args)
{
	if (!head)
		return ;
	*args = generate_results(head);
	free_segments(head);
	safe_free((void **)&file->directory);
	closedir(file->dir);
	safe_free((void **)&file);
}

/**
 * Function: generate_results
 * -----------------
 * This function generates a char *string concatenating every segment 
 * of the linked list and returns it to the tokenizer be able to set
 * the expanded content of '*' to it's content field, and calls the
 * finish_wild function in order to free the segments list.
 * 
 * @param: *segments: The head of the linked list.
 * @param: *file: The structure that contains the directory, token, etc.
 * @var: *result: The string that will be returned.
 * 
 * @return: char *.
 * 
*/

char	*generate_results(t_segment *segments)
{
	char	*result;

	result = NULL;
	while (segments)
	{
		if (!ft_strlen(result))
			result = gnl_strjoin(result, segments->str);
		else
		{
			result = gnl_strjoin(result, " ");
			result = gnl_strjoin(result, segments->str);
		}
		segments = segments->next;
	}
	return (result);
}

/**
 * Function: handle_wildcard
 * -----------------
 * This function handles the wildcard expansion. For expand wildcard
 * we need to know the directory and the token. The directory is the
 * path to the file and the token is the combination of the file name
 * and the wildcard *. This function will open the directory and read
 * the files inside it, after that it will check if the files and the
 * token match. If they match, the file will be added to the linked list.
 * 
 * @param: *pattern: The pattern that contains the wildcard.
 * @var: *file: The structure that contains the directory, token, etc.
 * @var: *head: The head of the linked list.
 * @var: opendir: The directory stream, used to open the directory.
 * @var: readdir: The directory entry, used to read the files at the directory.
 * @var: stat: The structure that contains the file information.
 * @var: closedir: The function that closes the directory stream.
 * 
 * @return: void
 * 
 */

void	handle_wildcard(char **args)
{
	t_file		*file;
	t_segment	*head;

	head = NULL;
	file = ft_calloc(1, sizeof(t_file));
	init_structs(file, 0, sizeof(t_file));
	get_dir_and_token(file, *args);
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

/**
 * Function: get_dir_and_token
 * -----------------
 * This function is used to separate the directory and the token. The	
 * directory needs to start with '/' (in case of relative/absolute path)
 * or '.' (current directory). Besides that, directory can't contain
 * wildcard for the correct work of the function 'opendir'. Now, the
 * token is the combination of the file name and the wildcard *. For
 * handle the directory and the token, we use the function 'strtok'.
 * This will separate the path having as delimiter the '/' character.
 * Then temp_token will have mini paths that will be concatenated with
 * the directory. When ft_strchr finds the wildcard, the loop will stop
 * and the file->token will be the last temp_token (with the wildcard).
 * Then we use ft_strcspn to get the length of the directory (without the
 * wildcard) and copy it to file->directory. 
 *   
 * @param: *file: The structure that contains the directory, token, etc.
 * @param: *pattern: The pattern that contains the wildcard.
 * @var: *temp_token: The temporary token that will storage the mini paths.
 * @var: temp_dir: The temporary directory that will be concatenated with
 * the directory.
 * @var: len: The length of the directory.
 * 
 * @return: void
 * 
 */

static void	get_dir_and_token(t_file *file, char *pattern)
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
		strcat(temp_dir, temp_token);
		if (temp_token && !ft_strchr(temp_token, '*'))
			strcat(temp_dir, "/");
		file->token = temp_token;
		temp_token = ft_strtok(NULL, "/");
	}
	len = ft_strcspn(temp_dir, "*");
	file->directory = ft_strndup(temp_dir, len);
}

/**
 * Function: wildcard_match
 * -----------------
 * This is a recursive function that checks if the files and the token
 * match. The function will iterate through the file until it finds the
 * wildcard. When it finds the wildcard, it will check if the file and
 * the token match, character by character. If they match, the function
 * will return true. If they don't match, the function will return false. 
 *   
 * @param: *file: The name of the file.
 * @param: *pattern: The pattern that contains the wildcard.
 * 
 * @return: true or false
 * 
 */

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
