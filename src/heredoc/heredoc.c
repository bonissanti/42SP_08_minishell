/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/16 19:10:54 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/temp.h"
#include "../include/hash.h"
#include "../include/segments.h"

// t_bool check_heredoc(char *in_fd)
// {
	
// }


void	check_expansion(t_exec *exec, t_hashtable *env, char **line)
{
	t_lex *dollar;
	t_segment *head;
	size_t len;

	dollar = init_lex(env, *line);
	head = NULL;
	len = 0;
	
	
}

t_bool	start_heredoc(t_exec *exec, t_hashtable *env, char *delim)
{
	char	*line;
	int		fd;

	fd = open(delim, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (false);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		// function to check for expansion
		// check_expansion(exec, env, &line);
		// free(line);
		// line = NULL;
	}
}