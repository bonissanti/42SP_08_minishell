/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:49:19 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/21 16:49:40 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// Funções de exemplo para os builtins
void	cd(void)
{
	printf("Executando cd\n");
}
void	echo(void)
{
	printf("Executando echo\n");
}
void	pwd(void)
{
	printf("Executando pwd\n");
}
void	unset(void)
{
	printf("Executando unset\n");
}
void	export(void)
{
	printf("Executando export\n");
}
void	env(void)
{
	printf("Executando env\n");
}
void	exit(void)
{
	printf("Executando exit\n");
}

// Estrutura para agrupar as funções e a matriz de funções
typedef struct
{
	void	(*builtins[])(void);
	void	(*execute_builtin)(struct Builtins *builtins, char *args);
}			Builtins;

// Função para verificar e executar o builtin
void	execute_builtin(Builtins *builtins, char *args)
{
	int	builtin_index;

	// Suponha que args é um número entre 0 e 6
	builtin_index = atoi(args);
	builtins->builtins[builtin_index]();
}

int	main(void)
{
	char	*args;

	Builtins builtins = {
		.builtins = {cd, echo, pwd, unset, export, env, exit},
		.execute_builtin = execute_builtin};
	args = "1";
	builtins.execute_builtin(&builtins, args);
	return (0);
}
