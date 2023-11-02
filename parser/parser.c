/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:04:14 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/01 22:15:08 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

// int	command_consistency(char *cmd)
// {
// 	if(*cmd == PIPE || cmd[ft_strlen(cmd) - 1] == PIPE)
// 		return (0);
// 	return (1);
// }

void handle_token(t_global *global, char *str)
{
	if(*str == '(')
		add_tkn_list(global, new_tkn_list(str, O_PARENTESIS));
	else if(*str == ')')
		add_tkn_list(global, new_tkn_list(str, C_PARENTESIS));
	else if(!ft_strncmp(str, ">>", 2))
		add_tkn_list(global, new_tkn_list(str, APPEND));
	else if(*str == '>')
		add_tkn_list(global, new_tkn_list(str, REDIRECT));
	else if(!ft_strncmp(str, "<<", 2))
		add_tkn_list(global, new_tkn_list(str, HERE_DOC));
	else if(*str == '<')
		add_tkn_list(global, new_tkn_list(str, INFILE));
	else if(!ft_strncmp(str, "||", 2))
		add_tkn_list(global, new_tkn_list(str, OR));
	else if(*str == '|')
		add_tkn_list(global, new_tkn_list(str, PIPE));
	else if(!ft_strncmp(str, "&&", 2))
		add_tkn_list(global, new_tkn_list(str, AND));
	else if(*str == '$')
		add_tkn_list(global, new_tkn_list(str, EXPAND));
	else if(*str == '*')
		add_tkn_list(global, new_tkn_list(str, WILD));
	else
		add_tkn_list(global, new_tkn_list(str, IDENTIFIER));
}

char *crop_tkn(char **cmd)
{
	char *cropped;
	int i;
	char quote;
	
	cropped = *cmd;
	i = 0;
	if (**cmd == '\'' || **cmd == '"')
	{
		quote = **cmd;
		i++;
		(*cmd)++;
		while(**cmd != quote)
		{
			i++;
			(*cmd)++;
		}
		i++;
		(*cmd)++;
	}
	else if(isdelimiter(*cmd))
	{
		if(**cmd == '$')
		{
			i++;
			(*cmd)++;
			while(**cmd != ' ' && **cmd != '\0' && !isdelimiter(*cmd))
			{
				i++;
				(*cmd)++;
			}
		}
		else if(!ft_strncmp(*cmd, "||", 2) || !ft_strncmp(*cmd, "&&", 2)
		|| !ft_strncmp(*cmd, "<<", 2) || !ft_strncmp(*cmd, ">>", 2))
		{
			i = 2;
			(*cmd) += 2;
		}
		else
		{
			i++;
			(*cmd)++;
		}
	}
	else
	{
		while(**cmd != ' ' && **cmd != '\0' && !isdelimiter(*cmd)) //here 
		{
			i++;
			(*cmd)++;
		}
	}
	return(ft_substr(cropped, 0, i));
} 

void tokenizer(t_global *global, char *cmd)
{
	char *actual_cmd;

	actual_cmd = cmd;
	while(*actual_cmd)
	{
		if(ft_isspace(*actual_cmd))
			skip_spaces(&actual_cmd);
		if(!(*actual_cmd))
			return ;
		handle_token(global, crop_tkn(&actual_cmd));
	}
}

//crop_tkn test:

// int main (void)
// {
// 	char *command = ft_strdup("echo \"teste\"");
// 	ft_printf("%s\n", crop_tkn(&command));
// 	ft_printf("%s\n", command);
// 	skip_spaces(&command);
// 	ft_printf("%s\n", crop_tkn(&command));
// }

// int main(void)
// {
// 	t_global global;
	
// 	// tokenizer(&global, "echo -n \"test\"");
// 	// tokenizer(&global, "<< qwerty > ./output| < ./infile wc -l > ./output &&echo \"test\" || (sort ./test)");
// 	// tokenizer(&global, "<teste.txt cat>teste.txtcat");
// 	// tokenizer(&global, "echo$PATH");
// 	// tokenizer(&global, "echo $PATH>path.txt&&cat path.txt|echo $USER");
// 	// tokenizer(&global, "echo $PATH>*.txt&&cat *.txt|echo $USER");
// 	print_tkn_list(global.tkn_list);
// }