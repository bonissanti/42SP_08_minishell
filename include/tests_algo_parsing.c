/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_algo_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:25:57 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/18 19:55:59 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "minishell.h"

const char *cursor;

t_bool my_pipe();
t_bool and();
t_bool or();
t_bool not();
t_bool redir();
t_bool my_command();

t_bool my_pipe()
{
	printf("%-16s Pipe: Command | Command\n", cursor);
	if (my_command() && strncmp(cursor, "||", 2) == 0 && my_command())
		return (is_true);
	else
		return (is_false);
}

t_bool and()
{
	printf("%-16s And: Command && Command\n", cursor);
	if (my_command() && strncmp(cursor, "&&", 2) == 0 && my_command())
		return (is_true);
	else
		return (is_false);
}

t_bool or()
{
	printf("%-16s Or: Command || Command\n", cursor);
	if (my_command() && strncmp(cursor, "||", 2) == 0 && my_command())
		return (is_true);
	else
		return (is_false);
}

t_bool not()
{
	printf("%-16s Not: ! Command\n", cursor);
	if (my_command() && *cursor == '!')
		return (is_true);
	else
		return (is_false);
}

t_bool redir()
{
	printf("%-16s Redir: Command > Command\n", cursor);
	if (my_command() && *cursor == '>' && my_command())
		return (is_true);
	else
		return (is_false);
}

t_bool word()
{
	printf("%-16s Word: [a-zA-Z0-9_]\n", cursor);
	if ((*cursor >= 'a' && *cursor <= 'z') || (*cursor >= 'A' && *cursor <= 'Z') || (*cursor >= '0' && *cursor <= '9') || *cursor == '_')
		return (is_true);
	else
		return (is_false);
}

t_bool my_command()
{
	printf("%-16s Command: Word\n", cursor);
	if (word())
		return (is_true);
	
	printf("%-16s Command: Pipe\n", cursor);
	if (my_pipe())
		return (is_true);
	
	printf("%-16s Command: And\n", cursor);
	if (and())
		return (is_true);

	printf("%-16s Command: Or\n", cursor);
	if (or())
		return (is_true);
		
	printf("%-16s Command: Not\n", cursor);
	if (not())
		return (is_true);

	printf("%-16s Command: Redir\n", cursor);
	if (redir())
		return (is_true);
	return (is_false);
}



int main(void)
{
	char string[64];

	puts("Enter a string: ");
	scanf("%s", string); // read the input of the user
	cursor = string;

	if (my_command())
	{
		puts("---------------------");
		puts("Parsing successful!");
		return (0);
	}
	else
	{
		puts("---------------------");
		puts("Parsing failed!");
		return (1);
	}
}