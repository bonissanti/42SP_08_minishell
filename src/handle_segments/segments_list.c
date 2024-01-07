/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:34:49 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/07 14:40:02 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lex	*init_lex(t_hashtable *env, char *arg)
{
	t_lex	*quote;

	quote = (t_lex *)ft_calloc(1, sizeof(t_lex));
	quote->ptr = gb_to_free(arg);
	quote->segment = (char *)ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	quote->env = env;
	init_structs(&quote->state, false, sizeof(t_quote_bool));
	init_structs(&quote->dollar, false, sizeof(t_expand));
	return (quote);
}

t_segment	*new_segments(char *str)
{
	t_segment	*cmd;

	cmd = (t_segment *)ft_calloc(1, sizeof(t_segment));
	cmd->str = ft_strdup(str);
	cmd->next = NULL;
	return (cmd);
}

void	add_segments(t_segment **head, char *str)
{
	t_segment	*current;

	if (*head == NULL)
		*head = new_segments(str);
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_segments(str);
	}
}

char	*join_segments(t_segment *head)
{
	t_segment	*current;
	char		*str;
	char		*ptr;
	int			len;

	len = 0;
	current = head;
	while (current)
	{
		len += ft_strlen(current->str);
		current = current->next;
	}
	str = (char *)ft_calloc(len + 1, sizeof(char));
	ptr = str;
	current = head;
	while (current)
	{
		strcpy(ptr, current->str);
		ptr += ft_strlen(current->str);
		current = current->next;
	}
	*ptr = '\0';
	return (str);
}

void	free_segments(t_segment *head)
{
	t_segment	*current;
	t_segment	*next;

	current = head;
	if (!current)
		return ;
	while (current)
	{
		next = current->next;
		safe_free((void **)&current->str);
		safe_free((void **)&current);
		current = next;
	}
}
