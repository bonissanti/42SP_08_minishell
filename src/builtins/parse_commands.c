/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:11:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/08 19:49:28 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "segments.h"

void parse_quotes(t_hashtable *env, char **args);

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

char get_quote_type(char c)
{
	if (c == '\"')
		return (1);
	else if (c == '\'')
		return (2);
	else
		return (0);
}


size_t is_even_quotes(char *str)
{
	size_t single_quotes;
	size_t double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*str)
	{
		if (*str == '\'')
			single_quotes++;
		else if (*str == '\"')
			double_quotes++;
		str++;
	}
	return (single_quotes % 2 == 0 && double_quotes % 2 == 0);
}

size_t ft_strcspn(const char *str, char *delim1, char *delim2)
{
	size_t i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == *delim1 || str[i] == *delim2)
			return (i);
	return (i);
}

void process_segment(t_quote *quote, t_segment *head, size_t len)
{
    if (len > 0)
    {
        quote->segment[len] = '\0';
        add_segments(&head, quote->segment);
    }
}

void parse_quotes(t_hashtable *env, char **args)
{
    t_quote quote;
    t_segment *head;
    size_t len;
    char *key;
    int key_len;
    t_hash *hash;

    len = 0;
    head = NULL;
    quote.ptr = *args;
    quote.env = env;
    quote.prev_type = 0;
    quote.segment = (char *)malloc(sizeof(char) * ft_strlen(*args) + 1);

    if (!is_even_quotes(*args))
    {
        ft_putstr_fd("minishell: syntax error: unexpected EOF\n", 2);
        free(quote.segment);
        exit(2);
    }
    while (*(quote.ptr))
    {
        quote.type = get_quote_type(*(quote.ptr));
        if (quote.type && quote.prev_type == *(quote.ptr))
        {
            process_segment(&quote, &head, len);
            len = -1;
            quote.prev_type = 0;
        }
        else if (quote.type && quote.prev_type == 0)
            quote.prev_type = *(quote.ptr);
        else if (*quote.ptr == '$' && (quote.type == 0 || quote.type == 2))
        {
            quote.ptr++;
            key_len = ft_strcspn(quote.ptr, "\"", "'");
            key = strndup(quote.ptr, key_len);
            hash = search(quote.env, key);
            if (hash)
                add_segments(&head, hash->value);
            free(key);
            quote.ptr += key_len - 1;
        }
        else
            quote.segment[len++] = *(quote.ptr);
        quote.ptr++;
    }
    process_segment(&quote, head, len);
    free(quote.segment);
    *args = join_segments(head);
    free_segments(head);
}


// void process_segment(t_quote *quote, t_segment *head, size_t len)
// {
// 	char *key;
// 	int	key_len;
// 	t_hash *hash;

// 	if (len > 0)
// 	{
// 		quote->segment[len] = '\0';
// 		add_segments(&head, quote->segment);
// 	}
// 	if (*(quote->ptr) == '$' && (quote->type == 0 || quote->type == 2))
// 	{
// 		quote->ptr++;
// 		key_len = ft_strcspn(quote->ptr, "\"", "'");
// 		key = strndup(quote->ptr, key_len);
// 		hash = search(quote->env, key);
// 		if (!hash)
// 			add_segments(&head, hash->value);
// 		free(key);
// 		quote->ptr += key_len;
// 	}
// }

// void	parse_quotes(t_hashtable *env, char **args)
// {
// 	t_quote 	quote;
// 	t_segment 	*head;
// 	size_t 		len;

// 	len = 0;
// 	head = NULL;
// 	quote.ptr = *args;
// 	quote.env = env;
// 	quote.prev_type = 0;
// 	quote.segment = (char *)malloc(sizeof(char) * ft_strlen(*args) + 1);

// 	if (!is_even_quotes(*args))
// 	{
// 		ft_putstr_fd("minishell: syntax error: unexpected EOF\n", 2);
// 		free(quote.segment);
// 		exit(2);
// 	}
// 	while (*(quote.ptr))
// 	{
// 		quote.type = get_quote_type(*(quote.ptr));
// 		if (quote.type && quote.prev_type == *(quote.ptr))
// 		{
// 			process_segment(&quote, head, len);
// 			len = -1;
// 			quote.prev_type = 0;
// 		}
// 		else if (quote.type && quote.prev_type == 0)
// 			quote.prev_type = *(quote.ptr);
// 		else
// 			quote.segment[len++] = *(quote.ptr);
// 		quote.ptr++;	
		
// 	}
// 	process_segment(&quote, head, len);
// 	// free(quote.segment);
// 	*args = join_segments(head);
// 	free_segments(head);	
// }


// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	t_hashtable *env = create_hashtable();
// 	init_hash(env, envp);
// 	insert(env, "VAR1", "value1");
// 	insert(env, "VAR2", "value2");

// 	// char *arg1 = ft_strdup("'\"\"\"\"\"$USER\"\"\"'");
// 	// char *arg2 = ft_strdup("echo '$VAR2' \"$HOME\" '\"$HOME\"'");
// 	// char *arg3 = ft_strdup("\"\"\"\"\"'$USER'\"\"\"");
// 	// char *arg4 = ft_strdup("\"$USER\"");
// 	// char *arg5 = ft_strdup("'$USER'");
// 	// char *arg6 = ft_strdup("$USER'");
// 	char *arg6 = ft_strdup("'"$USER"'");



// 	parse_quotes(env, &arg6);
// 	printf("%s\n", arg6);
// 	destroy_hashtable(env);
// 	free(arg6);
// 	return (0);
// }

