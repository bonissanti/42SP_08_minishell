/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:38:13 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/26 10:11:59 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_list *tests;
	
	ft_lstadd_back(&tests, ft_lstnew("echo hello world"));
	ft_lstadd_back(&tests, ft_lstnew("echo \"hello world\""));
	ft_lstadd_back(&tests, ft_lstnew("echo 'hello world'"));
	ft_lstadd_back(&tests, ft_lstnew("echo hello'world'"));
	ft_lstadd_back(&tests, ft_lstnew("echo hello\"\"world"));
	ft_lstadd_back(&tests, ft_lstnew("echo ''"));
	ft_lstadd_back(&tests, ft_lstnew("echo \"$PWD\""));
	ft_lstadd_back(&tests, ft_lstnew("echo '$PWD'"));
	ft_lstadd_back(&tests, ft_lstnew("echo \"aspas ->'\""));
	ft_lstadd_back(&tests, ft_lstnew("echo \"aspas -> ' \""));
	ft_lstadd_back(&tests, ft_lstnew("echo 'aspas ->\"'"));
	ft_lstadd_back(&tests, ft_lstnew("echo 'aspas -> \" '"));
	ft_lstadd_back(&tests, ft_lstnew("echo \"> >> < * ? [ ] | ; [ ] || && ( ) & # $ \\ <<\"")); 
	ft_lstadd_back(&tests, ft_lstnew("echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \\ <<'")); 
	ft_lstadd_back(&tests, ft_lstnew("echo \"exit_code ->$? user ->$USER home -> $HOME\"")); //FAIL 
	ft_lstadd_back(&tests, ft_lstnew("echo 'exit_code ->$? user ->$USER home -> $HOME'"));
	ft_lstadd_back(&tests, ft_lstnew("echo \"$\""));
	ft_lstadd_back(&tests, ft_lstnew("echo '$'"));
	ft_lstadd_back(&tests, ft_lstnew("echo $"));
	ft_lstadd_back(&tests, ft_lstnew("echo $?"));
	ft_lstadd_back(&tests, ft_lstnew("echo $?HELLO"));
 	init_hash(envp);
	prompt(g_global.hash, tests);
	return (g_global.exit_status);
}

// echo Lorem Ipsum is simply dummy text of the printing and typesetting industry. $PATH Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book

