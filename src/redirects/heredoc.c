/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/24 17:21:34 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/temp.h"
#include "../include/hash.h"
#include "../include/segments.h"


void print_pipe_contents(int pipefd[2]) {
    char buffer[1024];
    int bytes;

    // Close the write end of the pipe
    close(pipefd[1]);

    // Read from the pipe
    while ((bytes = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes] = '\0';  // Null-terminate the string
        ft_fprintf(1, "%s", buffer);
    }

    // Close the read end of the pipe
    close(pipefd[0]);
}

char *check_expansion(t_hashtable *env, char **line, size_t *len)
{
	t_lex *quote;
	t_segment *head;
	char *expanded;
	
	quote = init_lex(env, *line);
	head = NULL;
	expanded = NULL;
	while (*quote->ptr)
	{
		if (*quote->ptr == '$')
			expand_variable(quote, &head, len);
		else
		{
			quote->segment[*len] = *quote->ptr;
			(*len)++;
		}
		quote->ptr++;
	}
	quote->segment[*len] = '\0';
	add_segments(&head, quote->segment);
	expanded = join_segments(head);
	free_segments(head);
	free(quote->segment);
	free(quote);
	return (expanded);
}

void	handle_heredoc(t_hashtable *env, char *delim)
{
	int		pipefd[2];
	// int		fd;
	char	*line;
	size_t 	len;
	pipe(pipefd);
	while (1)
	{
		len = 0;
		line = readline("> ");
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		line = check_expansion(env, &line, &len);
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	print_pipe_contents(pipefd);
}