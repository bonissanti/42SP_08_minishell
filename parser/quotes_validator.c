#include "./hash.h"
#include "./segments.h"

size_t even_close_quotes(char *str) 
{
	t_quote_bool	state;
	
	init_structs(&state, false, sizeof(t_quote_bool));
	while (*str)
	{
		if (*str == '\\' && !state.escape_next && !state.single_open)
			state.escape_next = true;
		else if (state.escape_next)
			state.escape_next = false;
		else if (*str == '\'' && !state.double_open)
			state.single_open = !state.single_open;
		else if ((*str == '\"' && !state.single_open) 
			&& (!state.escape_next || state.escape_next))
			state.double_open = !state.double_open;
		str++;
	}
	return (!state.single_open && !state.double_open);
}

t_bool	check_dollar_space(char *str)
{
	while (*str)
	{
		if (*str == '$')
		{
			if (is_whitespace(*(str + 1)))
				return (true);
		}
		str++;
	}
	return (false);
}