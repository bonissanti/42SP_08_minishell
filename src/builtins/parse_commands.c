/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:11:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/10 18:49:07 by brunrodr         ###   ########.fr       */
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
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else
		return (0);
}


size_t even_close_quotes(char *str) // Testar '$ USER' e "$ USER" com o main do minishell
{
	size_t single_quotes;
	size_t double_quotes;
	t_bool is_squote_open;
	t_bool is_dquote_open;

	single_quotes = 0;
	double_quotes = 0;
	is_squote_open = false;
	is_dquote_open = false;
	while (*str)
	{
		if (*str == '\'' && !is_dquote_open)
		{
			single_quotes++;
			is_squote_open = !is_squote_open;
		}
		else if (*str == '\"' && !is_squote_open)
		{
			double_quotes++;
			is_dquote_open = !is_dquote_open;
		}
		str++;
	}
	return (single_quotes % 2 == 0 && double_quotes % 2 == 0);
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

// t_bool check_spaces_after_dollar(char *str)
// {
// 	char *ptr;
	
// 	ptr = str;
// 	while (*ptr)
// 	{
// 		if (*ptr == '$')
// 		{
// 			if (is_whitespace(*ptr))
// 				return (false);
// 		}
// 		ptr++;
// 	}
// 	return (true);
// }

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
	quote.type = 0;
    quote.prev_type = 0;
    quote.segment = (char *)malloc(sizeof(char) * ft_strlen(*args) + 1);

    if (!even_close_quotes(*args))
    {
        ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
        free(quote.segment);
        return ;
    }
    while (*(quote.ptr))
    {
		if (*quote.ptr == '\'' || *quote.ptr == '\"') // Define open quote
        	quote.type = get_quote_type(*(quote.ptr));
        if (quote.type && quote.prev_type == *(quote.ptr)) // Add segment to list when ptr is in close quote
        {
			quote.segment[len] = '\0';
            add_segments(&head, quote.segment);
            len = 0;
            quote.prev_type = 0;
			quote.type = 0;
        }
        else if (quote.type && quote.prev_type == 0) // Define close quote
            quote.prev_type = *(quote.ptr);
        else if (*quote.ptr == '$' && (quote.type == 0 || quote.type == 2)) // Expand variable
        {
			quote.ptr++;
			if (is_whitespace(*quote.ptr))
				quote.segment[len++] = '$';
            key_len = ft_strcspn(quote.ptr, "\"", "'");
            key = strndup(quote.ptr, key_len); 
            hash = search(quote.env, key);
            if (hash)
                add_segments(&head, hash->value);
            free(key);
            quote.ptr += key_len - 1;
		}
        else
            quote.segment[len++] = *(quote.ptr); // Add char to segment
        quote.ptr++;
    }
	if (quote.prev_type != 0)
	{
		ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
		free(quote.segment);
		return ;
	}
	
	quote.segment[len] = '\0';
    add_segments(&head, quote.segment);
    free(quote.segment);
    *args = join_segments(head);
	for (int i = 0; args[i]; i++)
		printf("%s ", args[i]);
	printf("\n");
    free_segments(head);
}

	// if (quote.type != 0)
	// {
	// 	ft_putstr_fd("minishell: syntax error: unexpected EOF\n", 2);
	// 	return ;
	// }


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

