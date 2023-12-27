/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:38:13 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/27 00:01:15 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_list *tests = NULL;
	ft_lstadd_back(&tests, ft_lstnew("echo 1 hello world"));
	ft_lstadd_back(&tests, ft_lstnew("echo 2 \"hello world\""));
	ft_lstadd_back(&tests, ft_lstnew("echo 3 'hello world'"));
	ft_lstadd_back(&tests, ft_lstnew("echo 4 hello'world'"));
	ft_lstadd_back(&tests, ft_lstnew("echo 5 hello\"\"world"));
	ft_lstadd_back(&tests, ft_lstnew("echo 6 - \"\" \"  \" hello"));
	ft_lstadd_back(&tests, ft_lstnew("echo 7 ''"));
	ft_lstadd_back(&tests, ft_lstnew("echo 8 \"$PWD\""));
	ft_lstadd_back(&tests, ft_lstnew("echo 9 '$PWD'"));
	ft_lstadd_back(&tests, ft_lstnew("echo 10 \"aspas ->'\""));
	ft_lstadd_back(&tests, ft_lstnew("echo 11 \"aspas -> ' \""));
	ft_lstadd_back(&tests, ft_lstnew("echo 12 'aspas ->\"'"));
	ft_lstadd_back(&tests, ft_lstnew("echo 13 'aspas -> \" '"));
	ft_lstadd_back(&tests, ft_lstnew("echo 14 \"> >> < * ? [ ] | ; [ ] || && ( ) & # $ \\ <<\"")); 
	ft_lstadd_back(&tests, ft_lstnew("echo 15 '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \\ <<'")); 
	ft_lstadd_back(&tests, ft_lstnew("echo 16 \"exit_code ->$? user ->$USER home -> $HOME\""));
	ft_lstadd_back(&tests, ft_lstnew("echo 17 'exit_code ->$? user ->$USER home -> $HOME'"));
	ft_lstadd_back(&tests, ft_lstnew("echo 18 \"$\""));
	ft_lstadd_back(&tests, ft_lstnew("echo 19 '$'"));
	ft_lstadd_back(&tests, ft_lstnew("echo 20 $"));
	ft_lstadd_back(&tests, ft_lstnew("echo 21 $?"));
	ft_lstadd_back(&tests, ft_lstnew("echo 22 $?HELLO"));
	ft_lstadd_back(&tests, ft_lstnew("echo 23 $?HE$?LLO$?"));
	// ft_lstadd_back(&tests, ft_lstnew("echo \"hi\" | cat | cat | cat | cat | cat | cat | cat"));
	// ft_lstadd_back(&tests, ft_lstnew("pwd"));
	// ft_lstadd_back(&tests, ft_lstnew("pwd oi"));
	// ft_lstadd_back(&tests, ft_lstnew("export hello"));
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO=123"));
	// ft_lstadd_back(&tests, ft_lstnew("export A-"));
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO=123 A"));
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO=\"123 A-\""));
	// ft_lstadd_back(&tests, ft_lstnew("export hello world"));
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO-=123 A"));
	// ft_lstadd_back(&tests, ft_lstnew("export ="));
	// ft_lstadd_back(&tests, ft_lstnew("export 123"));
	// ft_lstadd_back(&tests, ft_lstnew("unset"));
	// ft_lstadd_back(&tests, ft_lstnew("unset HELLO"));
	// ft_lstadd_back(&tests, ft_lstnew("unset HELLO1 HELLO2"));
	// ft_lstadd_back(&tests, ft_lstnew("unset HOME"));
	// ft_lstadd_back(&tests, ft_lstnew("unset PATH"));
	// ft_lstadd_back(&tests, ft_lstnew("unset SHELL"));
	// ft_lstadd_back(&tests, ft_lstnew("cd $PATH"));
	// ft_lstadd_back(&tests, ft_lstnew("cd $PATH oi"));
	// ft_lstadd_back(&tests, ft_lstnew("cd 123123"));
	// ft_lstadd_back(&tests, ft_lstnew("exit 123"));
	// ft_lstadd_back(&tests, ft_lstnew("exit 298"));
	// ft_lstadd_back(&tests, ft_lstnew("exit +100"));
	// ft_lstadd_back(&tests, ft_lstnew("exit \"+100\""));
	// ft_lstadd_back(&tests, ft_lstnew("exit -100"));
	// ft_lstadd_back(&tests, ft_lstnew("exit \"-100\""));
	// ft_lstadd_back(&tests, ft_lstnew("exit -\"100\""));
	// ft_lstadd_back(&tests, ft_lstnew("exit hello"));
	// ft_lstadd_back(&tests, ft_lstnew("exit 42 world"));
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile"));
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | wc"));
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | sort | wc"));
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile > outfile"));
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | wc > outfile"));
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | sort | wc > outfile"));
 	init_hash(envp);
	prompt(g_global.hash, tests);
	return (g_global.exit_status);
}

// echo Lorem Ipsum is simply dummy text of the printing and typesetting industry. $PATH Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book

