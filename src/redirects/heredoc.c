/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:50:15 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 18:42:54 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/segments.h"

char	*check_expansion(t_hashtable *env, char **line, size_t *len)
{
	t_lex		*quote;
	t_segment	*head;
	char		*expanded;

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
	size_t	len;

	if (delim == NULL)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token EOF\n");
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
