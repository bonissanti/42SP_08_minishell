/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:04:14 by aperis-p          #+#    #+#             */
/*   Updated: 2023/10/30 20:39:44 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

int	command_consistency(char *cmd)
{
	if(*cmd == PIPE || cmd[ft_strlen(cmd) - 1] == PIPE)
		return (0);	
}

void handle_delimiter_token(char *str)
{
	if(*str == '(')
		new_tkn_list(str, O_PARENTESIS);
	else if(*str == ')')
		new_tkn_list(str, C_PARENTESIS);
	else if(*str == '>')
		new_tkn_list(str, REDIRECT);
	else if(!ft_strncmp(str, '>>', 2))
		new_tkn_list(str, APPEND);
	else if(*str == '<')
		new_tkn_list(str, INFILE);
	else if(!ft_strncmp(str, '<<', 2))
		new_tkn_list(str, HERE_DOC);
	else if(*str == '|')
		new_tkn_list(str, PIPE);
	else if(!ft_strncmp(str, '&&', 2))
		new_tkn_list(str, AND);
	else
		new_tkn_list(str, OR);		
}

void tokenizer(char *cmd)
{
	while(cmd && !isdelimiter(*cmd))
	{
		char *actual_cmd;

		actual_cmd = cmd;
		if(ft_isspace(*actual_cmd))
			skip_spaces(actual_cmd);
		if(isdelimiter(actual_cmd))
			handle_delimiter_token(crop_tkn(actual_cmd));
		else
			handle_identifier_token(crop_tkn(actual_cmd));
	}
}
