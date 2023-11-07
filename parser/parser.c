/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:21:28 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/06 18:42:00 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *tkn_type_symbol(t_tkn_type type)
{
	if(type == PIPE)
		return ("|");
	else if(type == O_PARENTESIS)
		return ("(");
	else if(type == C_PARENTESIS)
		return (")");
	else if(type == AND)
		return ("&&");
	else if(type == OR)
		return ("||");
	return (NULL);
}

int	command_consistency(t_tkn_list *tokenized)
{
	t_tkn_list *head;
	t_tkn_list *tail;

	head = tokenized;
	tail = last_tkn_list(tokenized);
	if(head->type ==  OR || head->type == AND
	|| head->type == PIPE || head->type == C_PARENTESIS)
	{
		ft_printf("syntax error near unexpected token `%s'\n", tkn_type_symbol(head->type));
		exit(2);
	}
	else if (tail->type == OR || tail->type == AND 
	|| tail->type == PIPE || tail->type == O_PARENTESIS)
	{
		ft_printf("syntax error near unexpected token `%s'\n", tkn_type_symbol(tail->type));
		exit(2);
	}
	return (1);
}

t_tkn_list *parser(t_global *g_global)
{
	t_tkn_list *parsed;
	// t_tkn_list *tokenized;
	parsed = NULL;
	command_consistency(g_global->tkn_list);
	
	/*
	Simple command 
	echo -n \"test\"
	indentifier + identifier + identifier
	*/

	/*
	Compound command
	<< qwerty wc -l > ./output && echo \"test\" || (sort ./test)
	here_doc + identifier + redirect + identifier + AND + identifier + identifier OR subshell identifier + identifier subshell
	*/
	
	/*
	Compound command
	< teste.txt cat > teste.txt"
	*/

	/*
	simple command
	echo $PATH
	*/
	
	/*
	Compound command
	echo $PATH > path.txt && cat path.txt | tr [a-A] | cat -e path.txt
	*/

	/*
	Precedence test
	<< qwerty wc -l > ./outputteste && echo \"testzzzzzzzzzzzzz\" && (<< sort sort > ./otherfile)
	*/

	return(parsed);
}
/*
<REDIRECTION> ::=  '>' <WORD>
                |  '<' <WORD>
                |  '>>' <WORD>
                |  '<<' <WORD>
				
<REDIRECTION-LIST> ::= <REDIRECTION>
                    |  <REDIRECTION-LIST> <REDIRECTION>

<SIMPLE-COMMAND> ::=  <SIMPLE-COMMAND-ELEMENT>
                   |  <SIMPLE-COMMAND> <SIMPLE-COMMAND-ELEMENT>

<COMMAND> ::=  <SIMPLE-COMMAND>
            |  <SHELL-COMMAND>
            |  <SHELL-COMMAND> <REDIRECTION-LIST>

<SUBSHELL> ::=  '(' <COMPOUND-LIST> ')'

<PIPELINE> ::=
       |  <COMMAND>

*/