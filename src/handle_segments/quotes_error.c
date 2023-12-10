#include "../include/builtins.h"
#include "../include/hash.h"
#include "../include/segments.h"

t_bool	check_handle_error(t_lex *quote, int i)
{
	if (i == 1)
	{
		if (quote->state.single_open || quote->state.double_open)
			error_close_quotes(quote);
	}
	return (false);
}

void	error_close_quotes(t_lex *quote)
{
	ft_fprintf(2, "minishell: syntax error: unexpected EOF\n");
	free(quote->segment);
	free(quote);
	return ;
}
