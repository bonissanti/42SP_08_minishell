/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:06:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/16 17:04:40 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/hash.h"

t_bool is_flag_n(char *arg);
char *expand_variable(t_hashtable *hash_table, char *arg);

int ft_echo(t_hashtable *hash_table, char **args)
{
	int i;
	char *arg;
	
	i = 0;
	while (args[++i] != NULL)
	{
		if (args[i][0] == '-' && is_flag_n(args[i]))
			continue ;
		arg = expand_variable(hash_table, args[i]);
		printf("%s ", arg);
	}
	printf("\n");
	return (0);
}

t_bool is_flag_n(char *arg)
{
	size_t i;

	i = 0;
	while (arg[++i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
	}
	return (true);
}

// char *expand_variable(t_hashtable *hash_table, char *arg)
// {
// 	t_hash *hash;
	
// 	if (arg[0] == '$')
// 	{
// 		hash = search(hash_table, arg + 1);
// 		if (hash != NULL)
// 			return (hash->value);
// 	}
// 	return (arg);
// }

// int main(void)
// {
// 	char *echo_args[] = {"echo", "hello", "world", NULL};
// 	ft_echo(echo_args);
// 	return 0;
// }