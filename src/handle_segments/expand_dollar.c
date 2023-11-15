#include "../include/env.h"
#include "../include/segments.h"

void	expand_variable(t_quote *quote, t_segment **head, size_t *len)
{
	char *key;
	int key_len;
	t_hash *hash;

	quote->segment[*len] = '\0';
	add_segments(head, quote->segment);
	*len = 0;
	quote->ptr++;
	if (!quote->state.space_dollar)
	{
		key_len = ft_strcspn(quote->ptr, "\"", "'");
		key = ft_strndup(quote->ptr, key_len); 
		hash = search(quote->env, key);
		if (hash)
			add_segments(head, hash->value);
		free(key);
		quote->ptr += key_len - 1;
	}
	else
	{
		quote->segment[*len] = '$';
		(*len)++;
		quote->ptr--;
	}
	
}