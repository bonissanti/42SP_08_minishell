/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:00:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/21 14:39:37 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"
#include "../include/hash.h"

void	is_cd(t_hashtable *hash_table, char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(hash_table, args);
}

void	is_pwd(t_hashtable *hash_table, char **args)
{
	if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(hash_table, args);
}

