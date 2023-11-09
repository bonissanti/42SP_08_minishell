/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:21:28 by aperis-p          #+#    #+#             */
/*   Updated: 2023/11/08 22:05:16 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *tkn_type_converter(t_tkn_type type)
{
	if(type == INFILE)
		return ("<");
	else if(type == REDIRECT)
		return (">");
	else if(type == HERE_DOC)
		return ("<<");
	else if (type == APPEND)
		return (">>");
	else if(type == O_PARENTESIS)
		return ("(");
	else if(type == C_PARENTESIS)
		return (")");
	else if(type == AND)
		return ("&&");
	else if(type == OR)
		return ("||");
	else
		return ("|");
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
		ft_printf("syntax error near unexpected token `%s'\n", tkn_type_converter(head->type));
		exit(2);
	}
	else if (tail->type == OR || tail->type == AND 
	|| tail->type == PIPE || tail->type == O_PARENTESIS)
	{
		ft_printf("syntax error near unexpected token `%s'\n", tkn_type_converter(tail->type));
		exit(2);
	}
	return (1);
}

int is_operator(t_tkn_type tkn)
{
	if(tkn == PIPE || tkn == AND || tkn == OR)
		return (true);
	return (false);
}

int is_redirect(t_tkn_type tkn)
{
	if(tkn == INFILE || tkn == REDIRECT
	|| tkn == HERE_DOC || tkn == APPEND)
		return (true);
	return (false);
}

void new_cmd_file_node(t_global *g_global, t_tkn_list *current)
{
	if (is_redirect(current->prev))
	{
		add_cmd_list((t_cmd_list){
			.type = TYPE_FILE,
			.args = current->content,
			.prec_weight = DEFAULT,
			});
		current = current->next;
		join_args(current);
	}
	add_cmd_list((t_cmd_list){
		.type = TYPE_COMMAND,
		.args = current->content,
		.prec_weight = DEFAULT,
		});
	while(current && current->type == IDENTIFIER)
	{	
		current = current->next;
		g_global->cmd_list->args = gnl_strjoin(g_global->cmd_list->args, current->content);
		if (current->next->type == REDIRECT || current->next->type == APPEND)
			g_global->cmd_list->outfile == current->next->next->content;
	}
	join_args(current);
}

void	new_redirect_node(t_global *g_global, t_tkn_list *current)
{
	e_bool has_here_doc;
		
	if(current->type == HERE_DOC)
		has_here_doc = true;
	else
		has_here_doc = false;		
	add_cmd_list((t_cmd_list){
		.type = TYPE_REDIRECT,
		.args = tkn_type_converter(current->type),
		.prec_weight = OP_REDIRECT,
		.here_doc = has_here_doc,
	});
	current = current->next;
	join_args(current);
}
void	new_subshell_node(t_global *g_global, t_tkn_list *current)
{
	add_cmd_list((t_cmd_list){
		.type = TYPE_OPERATOR,
		.args = tkn_type_converter(current->type),
		.prec_weight = DEFAULT,
	});	
	while(current->type != C_PARENTESIS)
	{
		g_global->cmd_list->args = gnl_strjoin(g_global->cmd_list->args, current->content);
		current = current->next;
	}
	g_global->cmd_list->args = gnl_strjoin(g_global->cmd_list->args, current->content);
	current = current->next;
	join_args(current);
}

void	new_operator_node(t_global *g_global, t_tkn_list *current)
{
	e_operator weight;
	
	if (current->type == PIPE)
		weight = OP_PIPE;
	else
		weight = OP_LOGICAL;
	add_cmd_list((t_cmd_list){
		.type = TYPE_OPERATOR,
		.args = tkn_type_converter(current->type),
		.prec_weight = weight,
	});	
	current = current->next;
	join_args(current);
}

t_cmd_list	*join_args(t_tkn_type *tkn_list)
{
	t_tkn_type	*current;
	t_cmd_list	cmd_list;
	
	current = tkn_list;
	while(current)
	{
		if(current->type == IDENTIFIER)
			new_cmd_file_node(&g_global, current);
		else if (is_redirect(current->type))
			new_redirect_node(&g_global, current);
		else if (current->type == O_PARENTESIS)
			new_subshell_node(&g_global, current);
		else if (is_operator(current->type))
			new_operator_node(&g_global, current);
		join_args(current);
	}
}

// t_type type_converter(t_tkn_type node)
// {
// 	if(node.type == )
// }

// t_cmd_list	*new_cmd_list(t_tkn_type node)
// {
// 	t_cmd_list	*node;

// 	node = (t_cmd_list *)malloc(sizeof(t_cmd_list));
// 	if (!node)
// 		return (NULL);
// 	if(node.type == )
// 	node->type = ;
// 	if(type == IDENTIFIER)
// 		node->content = content;
// 	else if(type == EXPAND)
// 		node->content = ft_substr(content, 1, ft_strlen(content) - 1);
// 	else
// 		node->content = NULL;
// 	node->next = NULL;
// 	node->prev = NULL;
// 	return (node);
// }

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