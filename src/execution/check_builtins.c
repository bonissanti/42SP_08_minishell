/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 12:33:29 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"
#include "../include/hash.h"



void	echo(char *args)
{
	printf("echo function called, %s\n", args);
}

void	export(char *args)
{
	printf("export function called, %s\n", args);
}

void	init_builtins(t_command *cmd)
{
	cmd[0].name = "echo";
	cmd[0].function = echo;
	cmd[1].name = "export";
	cmd[1].function = export;
}

void	execute_builtins(t_command *builtins, char *cmd, char *args)
{
	size_t 	i;

	i = -1;
	while (++i < 2)
	{
		if (strcmp(cmd, builtins[i].name) == 0)
		{
			builtins[i].function(args);
			return ;
		}
	}
}

int main(void)
{
	char *args[] = {"echo", "otario"};
	t_command builtins[2];
	init_builtins(builtins);
	execute_builtins(builtins, args[0], args[1]);
}