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

static void    handle_quotes(t_quote *quote, t_bool *is_squote_open, t_bool *is_dquote_open)
{
	if (*quote->ptr == '\'' && !*is_dquote_open)
		*is_squote_open = !*is_squote_open;
	else if (*quote->ptr == '\"' && !*is_squote_open)
		*is_dquote_open = !*is_dquote_open;
}

void	expand_variable(t_quote *quote, t_segment **head, size_t len)
{
	char *key;
	int key_len;
	t_hash *hash;

	quote->segment[len] = '\0';
	add_segments(head, quote->segment);
	len = 0;
	quote->ptr++;
	if (is_whitespace(*quote->ptr))
	{
		quote->segment[len++] = '$';
	}
	key_len = ft_strcspn(quote->ptr, "\"", "'");
	key = strndup(quote->ptr, key_len); 
	hash = search(quote->env, key);
	if (hash)
		add_segments(head, hash->value);
	free(key);
	quote->ptr += key_len - 1;
}

static void	add_char_to_segment(t_quote *quote, t_segment **head, size_t *len)
{
	quote->segment[*len] = *(quote->ptr); // Add char to segment
	(*len)++;
	if (*(quote->ptr + 1) == '\'' || *(quote->ptr + 1) == '\"')
	{
		quote->segment[*len] = '\0';
		add_segments(head, quote->segment);
		*len = 0;
	}
}

static void	error_close_quotes(t_quote *quote)
{
	ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
	free(quote->segment);
	return ;
}

void parse_quotes(t_hashtable *env, char **args)
{
    t_quote *quote;
    t_segment *head;
    size_t len;
    t_bool is_squote_open;
	t_bool is_dquote_open;
	t_bool is_escape_next;

    len = 0;
    head = NULL;
    quote = init_quote(env, *args);
    is_dquote_open = false;
	is_squote_open = false;

    if (!even_close_quotes(*args))
    {
        ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
        free(quote->segment);
        return ;
    }
    while (*(quote->ptr))
    {
		if ((*quote->ptr == '\'' && !is_dquote_open) || (*quote->ptr == '\"' && !is_squote_open))
			handle_quotes(quote, &is_squote_open, &is_dquote_open);
        else if (*quote->ptr == '$' && (is_dquote_open || (!is_squote_open && !is_dquote_open)))
            expand_variable(quote, &head, len);
        else if (is_squote_open || is_dquote_open)
			add_char_to_segment(quote, &head, &len);
        else
            quote->segment[len++] = *(quote->ptr);
        quote->ptr++;
    }
	if (is_squote_open || is_dquote_open)
		error_close_quotes(quote);
	quote->segment[len] = '\0';
    add_segments(&head, quote->segment);
    free(quote->segment);
    *args = join_segments(head);
	for (int i = 0; args[i]; i++)
		printf("%s ", args[i]);
	printf("\n");
    free_segments(head);
}

// if (*quote.ptr == '\'' && !is_dquote_open)
		// 	is_squote_open = !is_squote_open;
		// else if (*quote.ptr == '\"' && !is_squote_open)
		// 	is_dquote_open = !is_dquote_open;


// void parse_quotes(t_hashtable *env, char **args)
// {
//     t_quote quote;
//     t_segment *head;
//     size_t len;
//     char *key;
//     int key_len;
//     t_hash *hash;
//     t_bool is_squote_open;
// 	t_bool is_dquote_open;

//     len = 0;
//     head = NULL;
//     quote.ptr = *args;
//     quote.env = env;
//     quote.segment = (char *)malloc(sizeof(char) * ft_strlen(*args) + 1);
//     is_dquote_open = false;
// 	is_squote_open = false;

//     if (!even_close_quotes(*args))
//     {
//         ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
//         free(quote.segment);
//         return ;
//     }
//     while (*(quote.ptr))
//     {
// 		if (*quote.ptr == '\'' && !is_dquote_open)
// 			is_squote_open = !is_squote_open;
// 		else if (*quote.ptr == '\"' && !is_squote_open)
// 			is_dquote_open = !is_dquote_open;
//         else if (*quote.ptr == '$' && (is_dquote_open || (!is_squote_open && !is_dquote_open)))
//         {
//             quote.segment[len] = '\0';
//             add_segments(&head, quote.segment);
//             len = 0;
// 			quote.ptr++;
// 			if (is_whitespace(*quote.ptr))
// 				quote.segment[len++] = '$';
//             key_len = ft_strcspn(quote.ptr, "\"", "'");
//             key = strndup(quote.ptr, key_len); 
//             hash = search(quote.env, key);
//             if (hash)
//                 add_segments(&head, hash->value);
//             free(key);
//             quote.ptr += key_len - 1;
// 		}
	
//         else if (is_squote_open || is_dquote_open)
//         {
//             quote.segment[len++] = *(quote.ptr); // Add char to segment
//             if (*(quote.ptr + 1) == '\'' || *(quote.ptr + 1) == '\"')
//             {
//                 quote.segment[len] = '\0';
//                 add_segments(&head, quote.segment);
//                 len = 0;
//             }
//         }
//         else
//             quote.segment[len++] = *(quote.ptr); // Add char to segment
//         quote.ptr++;
//     }
// 	if (is_squote_open || is_dquote_open)
// 	{
// 		ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
// 		free(quote.segment);
// 		return ;
// 	}
// 	quote.segment[len] = '\0';
//     add_segments(&head, quote.segment);
//     free(quote.segment);
//     *args = join_segments(head);
// 	for (int i = 0; args[i]; i++)
// 		printf("%s ", args[i]);
// 	printf("\n");
//     free_segments(head);
// }
