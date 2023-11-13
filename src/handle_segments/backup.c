// void    handle_quotes(t_parse *quote, t_quote_state *status)
// {
//     if (*quote->ptr == '\'' && !status->double_open)
//         status->single_open = !status->single_open;
//     else if (*quote->ptr == '\"' && !status->single_open)
//         status->double_open = !status->double_open;
// }

// void    char_between_quotes(t_parse *parse, t_segment **head, t_quote_state *status, size_t *len)
// {
//     if (status->single_open || status->double_open)
//         parse->segment[*len] = *(parse->ptr);

//     if (*(parse->ptr + 1) == '\'' || *(parse->ptr + 1) == '\"')
//     {
//         parse->segment[*len] = '\0';
//         add_segments(head, parse->segment);
//         *len = 0;
//     }
// }

// void    parse_quotes(t_hashtable *env, char **args)
// {
//     t_parse         *parse;
//     t_segment       *head;
//     t_quote_state   status;
//     size_t          len;

//     len = 0;
//     head = NULL;
//     parse = init_parse(env, *args);
//     status.double_open = false;
//     status.single_open = false;

//     if (!even_close_quotes(*args)) //colocar essa função antes da chamada do parse_quotes
//     {
//         ft_putstr_fd("minishell: syntax error: unexpected EOF\n", 2);
//         free(parse->segment);
//         return ;
//     }
//     while (*(parse->ptr))
//     {
//         handle_quotes(parse, &status);
//         if (*parse->ptr == '$' && (status.double_open || (!status.single_open && !status.double_open)))
//             expand_variable(parse, &head, &len);
//         else if (!status.single_open && !status.double_open)
//             parse->segment[len++] = *(parse->ptr);
//         else if (status.single_open || status.double_open)
//             char_between_quotes(parse, &head, &status, &len);
//         parse->ptr++;
//     }
//     if (status.single_open || status.double_open)
//     {
//         ft_putstr_fd("minishell: syntax error: unexpected EOF\n", 2);
//         free(parse->segment);
//         return ;
//     }
//     parse->segment[len] = '\0';
//     add_segments(&head, parse->segment);
//     free(parse->segment);
//     *args = join_segments(head);
//     for (int i = 0; args[i]; i++) // remover depois
//         printf("%s ", args[i]);
//     printf("\n");
//     free_segments(head);
// }

// void    expand_variable(t_parse *parse, t_segment **head, size_t *len)
// {
//     char    *key;
//     int     key_len;
//     t_hash  *hash;

//     parse->segment[*len] = '\0';
//     add_segments(head, parse->segment);
//     len = 0;
//     parse->ptr++;
//     if (is_whitespace(*parse->ptr))
//         parse->segment[(*len)++] = '$';
//     key_len = ft_strcspn(parse->ptr, "\"", "'");
//     key = strndup(parse->ptr, key_len);
//     hash = search(parse->env, key);
//     if (hash)
//         add_segments(head, hash->value);
//     free(key);
//     parse->ptr += key_len - 1;
// }



//############################### FUNCIONA   ###################################

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

