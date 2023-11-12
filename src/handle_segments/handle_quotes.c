#include "../builtins/env.h"
#include "../include/segments.h"

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
