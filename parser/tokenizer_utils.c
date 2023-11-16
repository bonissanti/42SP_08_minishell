/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:54:44 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/15 23:25:38 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int is_expander(char x)
{
	if(x == '$' || x == '*' || x == '~')
		return (true);
	return(false);
}
char *append_expanded(char *cmd, char **exp, t_hashtable *env, int index)
{
	char *to_expand;

	to_expand = ft_substr(*exp, 0, crop_delimiter_tkn(exp));
	is_quotes(env, &to_expand);
	return(gnl_strjoin(ft_substr(cmd, 0, index), to_expand));
}
