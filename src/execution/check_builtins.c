/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/21 18:20:17 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"
#include "../include/hash.h"

void	cd(char **args)
{
	if (strcmp(args[0], "cd") == 0)
		printf("cd function called\n");
}



void	execute_builtins(t_builtins *pointer, char **args)
{
	pointer->builtins[pointer->index](args);
}

void	export(char **args)
{
	if (strcmp(args[0], "export") == 0)
		printf("export function called\n");
}


void	execute_builtin(char *builtin)
{
	if (strcmp(builtin, "cd") == 0)
		printf("cd function called\n");
	else if (strcmp(builtin, "export") == 0)
		printf("export function called\n");
	else if (strcmp(builtin, "unset") == 0)
		printf("unset function called\n");
	else if (strcmp(builtin, "env") == 0)
		printf("env function called\n");
	else if (strcmp(builtin, "exit") == 0)
		printf("exit function called\n");
	else if (strcmp(builtin, "pwd") == 0)
		printf("pwd function called\n");
	else if (strcmp(builtin, "echo") == 0)
		printf("echo function called\n");
	else
		printf("command not found\n");

}

// int	find_index(char *builtin)
// {
// 	if (strcmp(builtin, "cd") == 0)
// 		return (0);
// 	else if (strcmp(builtin, "export") == 0)
// 		return (1);
// 	else if (strcmp(builtin, "unset") == 0)
// 		return (2);
// 	else if (strcmp(builtin, "env") == 0)
// 		return (3);
// 	else if (strcmp(builtin, "exit") == 0)
// 		return (4);
// 	else if (strcmp(builtin, "pwd") == 0)
// 		return (5);
// 	else if (strcmp(builtin, "echo") == 0)
// 		return (6);
// 	else
// 		return (-1);
// }


int main(void)
{
	t_builtins pointer;
	char *args[2] = {"export", NULL};

	pointer.builtins[0] = cd;
	pointer.builtins[1] = export;
	pointer.builtins[2] = NULL;
	
	pointer.index = 1;
	ft_execute_builtins(&pointer, args);
}