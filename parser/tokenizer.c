/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:04:14 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/09 19:38:52 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

t_global g_global;

void handle_token(t_global *g_global, char *str)
{
	if(*str == '(')
		add_tkn_list(g_global, new_tkn_list(str, O_PARENTESIS));
	else if(*str == ')')
		add_tkn_list(g_global, new_tkn_list(str, C_PARENTESIS));
	else if(!ft_strncmp(str, ">>", 2))
		add_tkn_list(g_global, new_tkn_list(str, APPEND));
	else if(*str == '>')
		add_tkn_list(g_global, new_tkn_list(str, REDIRECT));
	else if(!ft_strncmp(str, "<<", 2))
		add_tkn_list(g_global, new_tkn_list(str, HERE_DOC));
	else if(*str == '<')
		add_tkn_list(g_global, new_tkn_list(str, INFILE));
	else if(!ft_strncmp(str, "||", 2))
		add_tkn_list(g_global, new_tkn_list(str, OR));
	else if(*str == '|')
		add_tkn_list(g_global, new_tkn_list(str, PIPE));
	else if(!ft_strncmp(str, "&&", 2))
		add_tkn_list(g_global, new_tkn_list(str, AND));
	else if(*str == '$')
		add_tkn_list(g_global, new_tkn_list(str, EXPAND));
	else if(*str == '*')
		add_tkn_list(g_global, new_tkn_list(str, WILD));
	else
		add_tkn_list(g_global, new_tkn_list(str, IDENTIFIER));
}

int crop_delimiter_tkn(char **cmd)
{
	int i;
	
	i = 0;
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
	return(i);
}

int crop_quote_tkn(char **cmd)
{
	int i;
	char quote;
	
	quote = **cmd;
	i = 1;
	(*cmd)++;
	while(**cmd != quote)
	{
		i++;
		(*cmd)++;
	}
	i++;
	(*cmd)++;
	return(i);
}

char *crop_tkn(char **cmd)
{
	char *cropped;
	int i;
	
	cropped = *cmd;
	i = 0;
	if (**cmd == '\'' || **cmd == '"')
		i = crop_quote_tkn(cmd);
	else if(isdelimiter(*cmd))
		i = crop_delimiter_tkn(cmd);
	else
	{
		while(**cmd != ' ' && **cmd != '\0' && !isdelimiter(*cmd))
		{
			i++;
			(*cmd)++;
		}
	}
	return(ft_substr(cropped, 0, i));
} 

void tokenizer(t_global *g_global, char *cmd)
{
	char *actual_cmd;

	actual_cmd = cmd;
	g_global->tkn_list = NULL;
	while(*actual_cmd)
	{
		if(ft_isspace(*actual_cmd))
			skip_spaces(&actual_cmd);
		if(!(*actual_cmd))
			return ;
		handle_token(g_global, crop_tkn(&actual_cmd));		
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

int main(void)
{
	
	// tokenizer(&g_global, "echo -n \"test\"");
	// tokenizer(&g_global, "<< qwerty > ./output| < ./infile wc -l > ./output &&echo \"test\" || (sort ./test)");
	// tokenizer(&g_global, "<teste.txt cat>teste.txtcat");
	// tokenizer(&g_global, "echo$PATH");
	// tokenizer(&g_global, "echo $PATH>path.txt&&cat path.txt|echo $USER");
	// tokenizer(&g_global, "echo $PATH>*.txt&&cat *.txt|echo $USER");
	// tokenizer(&g_global, "< ./parser.h wc -l > ./outfile");
	// tokenizer(&g_global, "<./parser.h wc -l>outfile");
	// tokenizer(&g_global, "< ./parser.h wc -l>outfile (");
	// tokenizer(&g_global, "<< qwerty wc -l > ./output && echo \"test\" || (sort ./test)");
	tokenizer(&g_global, "wc -l > ./output && echo \"test\" || (sort ./test)");
	// tokenizer(&g_global, "< ./parser.h wc -l>outfile (");
	print_tkn_list(g_global.tkn_list);
	parser();
}
