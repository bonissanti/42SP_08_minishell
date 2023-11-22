/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 13:04:28 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/temp.h"
#include "../include/hash.h"
#include "../include/segments.h"

// t_bool check_heredoc(char *in_fd)
// {
	
// }

// t_exec *init_exec(t_exec *exec)
// {
// 	t_exec *exec;
	
// 	exec->in_fd = 0;
// 	exec->out_fd = 1;
// 	exec->fd_heredoc = 0;
// 	exec->cmd_count = 0;
// 	exec->cmd = NULL;
// 	exec->delim = NULL;
// 	return (exec);
// }	

// t_line *init_list(t_line *list)
// {
// 	t_line *line;

// 	line = (t_line *)malloc(sizeof(t_line));
	
// 	line->content = NULL;
// 	line->next = NULL;
// 	return (line);
// }

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


void	handle_heredoc(t_hashtable *env, char *delim);

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
		if (!ft_strncmp(line, delim, ft_strlen(delim)))
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