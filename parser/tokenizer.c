/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:04:14 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/17 00:30:39 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	else if(*str == '*' || *str == '~')
		add_tkn_list(g_global, new_tkn_list(str, WILD));
	else
		add_tkn_list(g_global, new_tkn_list(str, IDENTIFIER));
}

int crop_delimiter_tkn(char **cmd)
{
	int i;
	
	i = 0;
	if(**cmd == '$' || **cmd == '~' || **cmd == '*')
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
		while(**cmd != quote)
		{
			i++;
			(*cmd)++;
		}
		i++;
		(*cmd)++;
		if(**cmd == '\'' || **cmd == '"')		
			quote = **cmd;
		else
			return(i);
		i++;
		(*cmd)++;		
	}
	i++;
	(*cmd)++;		
	return(i);
}

char *crop_tkn(char **cmd, t_hashtable *env)
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
		if(is_expander(**cmd))
			return(append_expanded(cropped, cmd, env, i));
	}
	return(ft_substr(cropped, 0, i));
} 

void tokenizer(t_global *g_global, char *cmd, t_hashtable *env)
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
		handle_token(g_global, crop_tkn(&actual_cmd, env));		
	}
}

int main(int argc, char **argv, char** envp)
{
	(void)argc;
	(void)argv;

	t_hashtable *hash = create_hashtable();
	init_hash(hash, envp);
	prompt(hash);
}
	// tokenizer(&g_global, "echo -n \"test\"", hash); // should not expand at cmd_list
	// tokenizer(&g_global, "echo$USER", hash);
	// tokenizer(&g_global, "echo -n ""test""teste $USER", hash);
	// tokenizer(&g_global, "echo \"\'\"\'\"$USER\"\'\"\'\""", hash);
	// tokenizer(&g_global, "echo "'"'"$USER"'"'"", hash);
	// tokenizer(&g_global, "<< qwerty > ./output| < ./infile wc -l > ./output &&echo \"test\" || (sort ./test)", hash);
	// tokenizer(&g_global, "<teste.txt cat>teste.txtcat", hash);
	// tokenizer(&g_global, "echo$PATH", hash);
	// tokenizer(&g_global, "echo $ PATH", hash);
	// tokenizer(&g_global, "echo $PATH>path.txt&&cat path.txt|echo $USER", hash);
	// tokenizer(&g_global, "echo $PATH>*.txt&&cat ~/output.txt|echo $USER", hash);
	// tokenizer(&g_global, "< ./parser.h wc -l > ./outfile", hash);
	// tokenizer(&g_global, "<./parser.h wc -l>outfile", hash);
	// tokenizer(&g_global, "< ./parser.h wc -l>outfile (", hash);
	// tokenizer(&g_global, "<< qwerty wc -l > ./output && echo \"test\" || (sort ./test)", hash); // need to fix the \"test\" behavior and also add the subshel treatment
	// tokenizer(&g_global, "wc -l > ./output && echo \"test\" || (sort ./test)", hash);
	// tokenizer(&g_global, "< ./parser.h wc -l>outfile", hash);
	// print_tkn_list(g_global.tkn_list);
	//./any.txt grep "'"'"any"'"'"
