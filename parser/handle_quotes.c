#include "./env.h"
#include "./segments.h"

static void	handle_quotes(t_quote *quote);
static void	char_between_quotes(t_quote *quote, t_segment **head, size_t *len);
static void	literal_string(t_quote *quote, size_t *len);
static void	final_process(t_quote *quote, t_segment **head, char **args,
				size_t *len);

void	is_quotes(t_hashtable *env, char **args)
{
	t_quote		*quote;
	t_segment	*head;
	size_t		len;

	len = 0;
	head = NULL;
	quote = init_quote(env, *args);
	// if (!even_close_quotes(*args))
	// {
	// 	ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
	// 	free(quote->segment);
	// 	return ;
	// }
	if (check_handle_error(quote, args, 0))
		return ;
	while (*(quote->ptr))
	{
		if ((*quote->ptr == '\'' && !quote->state.double_open)
			|| (*quote->ptr == '\"' && !quote->state.single_open))
			handle_quotes(quote);
		else if (*quote->ptr == '$' && (quote->state.double_open 
			|| (!quote->state.single_open && !quote->state.double_open)))
			expand_variable(quote, &head, &len);
		else if (quote->state.single_open || quote->state.double_open)
			char_between_quotes(quote, &head, &len);
		else
			literal_string(quote, &len);
		quote->ptr++;
	}
	check_handle_error(quote, args, 1);
	// if (!even_close_quotes(*args))
	// {
	// 	ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
	// 	free(quote->segment);
	// }
	final_process(quote, &head, args, &len);
}

static void	handle_quotes(t_quote *quote)
{
	if (*quote->ptr == '\'' && !quote->state.double_open)
		quote->state.single_open = !quote->state.single_open;
	else if (*quote->ptr == '\"' && !quote->state.single_open)
		quote->state.double_open = !quote->state.double_open;
}

static void	char_between_quotes(t_quote *quote, t_segment **head, size_t *len)
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

static void	literal_string(t_quote *quote, size_t *len)
{
	if (*quote->ptr == '\\')
	{
		quote->state.escape_next = true;
		quote->ptr++;
		quote->segment[*len] = *(quote->ptr);
		(*len)++;
		quote->state.escape_next = false;
	}
	else
	{
		quote->segment[*len] = *(quote->ptr);
		(*len)++;
	}
}

static void	final_process(t_quote *quote, t_segment **head, char **args,
		size_t *len)
{
	quote->segment[*len] = '\0';
	add_segments(head, quote->segment);
	free(quote->segment);
	free(quote);
	*args = join_segments(*head);
	// for (int i = 0; args[i]; i++) //retirar depois
	// 	printf("%s ", args[i]);
	// printf("\n");
	free_segments(*head);
}