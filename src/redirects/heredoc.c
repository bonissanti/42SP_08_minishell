/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/06 16:02:58 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"
#include "../include/segments.h"
#include "../include/exec.h"


void print_pipe_contents(int *pipefd)
{
    char buffer[1024];
    int bytes;

    // Close the write end of the pipe
    close(pipefd[1]);

    // Read from the pipe
    while ((bytes = read(pipefd[0], buffer, sizeof(buffer) - 1)) != 0) {
        buffer[bytes] = '\0';  // Null-terminate the string
        ft_fprintf(2, "%s", buffer);
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

// void	handle_heredoc(t_ast *node, t_hashtable *hash, char *delim)
// {
// 	int		fd;
// 	char	*line;
// 	size_t 	len;
// 	pid_t   pid;

// 	if (delim == NULL)
// 	{
// 		fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
// 		return ;
// 	}
// 	fd = open(delim, O_WRONLY | O_CREAT | O_TRUNC, 0644); // Cria um arquivo com o nome especificado
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(fd, STDOUT_FILENO); // Redireciona stdout para o arquivo
// 	while (1)
// 	{
// 		len = 0;
// 		line = readline("> ");
// 		if (!strcmp(line, delim))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		line = check_expansion(hash, &line, &len);
// 		printf("%s\n", line); // Agora escreve a linha no arquivo
// 		free(line);
// 	}
// 	close(fd); // Fecha o arquivo

// 	// Agora executa o comando cat no arquivo
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		// Processo filho
// 		char *argv[] = {"cat", delim, NULL};
// 		execvp(argv[0], argv);
// 		perror("execvp");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid < 0)
// 	{
// 		// Erro ao criar o processo
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		// Processo pai
// 		wait(NULL); // Espera o processo filho terminar
// 	}
// }

// void	execute_heredoc(t_ast *node, t_hashtable *hash, int *fd)
// {
// 	// pipe(fd);

// 	node->fd = fork();

// 	if (node->fd == 0)
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		// ft_printf_fd(STDIN_FILENO);
// 		execute_forked_command(hash, node);
// 		exit (EXIT_SUCCESS);
// 	}
// 	else if (node->fd == -1)
// 		ft_fprintf(2, "minishell: %s\n", strerror(errno));
// 	else
// 	{
// 		close(fd[1]);
// 	}
// }


void	handle_heredoc(t_ast *node, t_hashtable *hash, char *delim)
{
	int		fd[2];
	char	*line;
	size_t 	len;
	
	if (delim == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
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
	dup2(fd[0], STDIN_FILENO);
	if (node->left)
		execute_forked_command(hash, node->left);
}


// signals
// while (1)
// {	
///	
// }

