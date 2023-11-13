#include "../include/segments.h"


t_quote *init_quote(t_hashtable *env, char *arg)
{
    t_quote *quote;

    quote = (t_quote *)malloc(sizeof(t_quote));
    quote->ptr = arg;
    quote->segment = (char *)malloc(sizeof(char) * ft_strlen(arg) + 1);
    quote->segment[0] = '\0';
    quote->type = 0;
    quote->prev_type = 0;
    quote->env = env;
    quote->state.double_open = false;
    quote->state.single_open = false;
    return (quote);
}

t_segment *new_segments(char *str)
{
	t_segment *cmd;

	cmd = (t_segment *)malloc(sizeof(t_segment));
	cmd->str = ft_strdup(str);
	cmd->next = NULL;
	return (cmd);
}

void add_segments(t_segment **head, char *str)
{
	t_segment *current;

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

char *join_segments(t_segment *head)
{
	t_segment *current;
	char *str;
	char *ptr;
	int len;

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
	t_segment *current;
	t_segment *next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

size_t ft_strcspn(const char *str, char *delim1, char *delim2)
{
	size_t length;

	length = 0;
	while (*str)
	{
		if (*str == *delim1 || *str == *delim2)
			return (length);
		str++;
		length++;
	}
	return (length);
}

t_bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\0')
		return (true);
	return (false);
}