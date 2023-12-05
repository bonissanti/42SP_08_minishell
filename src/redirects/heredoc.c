/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/05 19:12:38 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"
#include "../include/segments.h"
#include "../include/exec.h"


void print_pipe_contents(int *pipefd) {
    char buffer[1024];
    int bytes;

    // Close the write end of the pipe
    close(pipefd[1]);

    // Read from the pipe
    while ((bytes = read(pipefd[0], buffer, sizeof(buffer) - 1)) != 0) {
        buffer[bytes] = '\0';  // Null-terminate the string
        ft_fprintf(2, "%s\n", buffer);
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


void	handle_heredoc(t_ast *node, t_hashtable *hash, char *delim)
{
	int		fd[2];
	char	*line;
	size_t 	len;
	
	// pipe(fd);
	if (delim == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	// node->fd = open("/tmp/fileXXXXXX", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipe(fd);
	while (1)
	{
		len = 0;
		line = readline("> ");
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		line = check_expansion(hash, &line, &len);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	print_pipe_contents(fd);
}

