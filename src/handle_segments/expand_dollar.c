/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:33:15 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/05 16:48:52 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	add_dollar_on_line(t_lex *quote, size_t *len)
{
	quote->segment[*len] = '$';
	(*len)++;
	quote->ptr--;
}

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
		if (*key == '?')
			add_segments(head, gb_to_free(ft_itoa(g_global.cmd_status)));
		else
		{
			hash = search(quote->env, key);
			if (hash && hash->value)
				add_segments(head, hash->value);
			quote->ptr += key_len - 1;
		}
		free(key);
	}
	else
		add_dollar_on_line(quote, len);
}
