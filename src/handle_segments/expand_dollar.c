/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:33:15 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/11 14:43:46 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_variable(t_lex *quote, t_segment **head, size_t *len)
{
	char	*key;
	int		key_len;
	t_hash	*hash;

	quote->segment[*len] = '\0';
	add_segments(head, quote->segment);
	*len = 0;
	quote->ptr++;
	if (!quote->state.space_dollar)
	{
		key_len = custom_strcspn(quote->ptr, "'");
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
