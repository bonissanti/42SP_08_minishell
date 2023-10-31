/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:39:50 by aperis-p          #+#    #+#             */
/*   Updated: 2023/10/30 18:21:53 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*skip_spaces(char *str)
{
	while (ft_isspace(*str))
		str++;
	return (str);
}
int isdelimiter(char *cmd)
{
	if(*cmd == '(' || *cmd == ')' || !ft_strncmp(cmd, '||', 2)
	|| *cmd == '|' || !ft_strncmp(cmd, '&&', 2))
		return(1);
	return(0);
}

