#include "../../minishell.h"

t_lex	*init_lex(t_hashtable *env, char *arg)
{
	t_lex	*quote;

	quote = (t_lex *)malloc(sizeof(t_lex));
	quote->ptr = arg;
	quote->segment = (char *)malloc(sizeof(char) * ft_strlen(arg) + 1);
	quote->env = env;
	init_structs(&quote->state, false, sizeof(t_quote_bool));
	init_structs(&quote->dollar, false, sizeof(t_expand));
	return (quote);
}

t_segment	*new_segments(char *str)
{
	t_segment	*cmd;

	cmd = (t_segment *)malloc(sizeof(t_segment));
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

// Merece uma atenção ao dar free, precisa ser fora da função
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
	str = (char *)malloc(sizeof(char) * len + 1);
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
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}
