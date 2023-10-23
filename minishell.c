/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:38:13 by aperis-p          #+#    #+#             */
/*   Updated: 2023/10/22 22:00:48 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	int	int_mode;
	int_mode = 1;
	// while (int_mode)
	// {
	// 	int_mode = isatty(STDIN_FILENO);
	// 	if (int_mode == 1)
	// 		ft_putstr_fd("~$ \n", 1);
	// }
	while (1)
		ft_putstr_fd("~$ \n", 1);
}
