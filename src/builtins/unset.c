/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:53:13 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/10 20:49:40 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_unset(t_hashtable *hash_table ,char **args)
{
    int i;

    i = 0;
    if (args[1] == NULL)
        ft_fprintf(2, "unset: not enough arguments\n");
    else
    {
        while (args[++i] != NULL)
            delete_hash(hash_table, args[i]);
    }
    return ;
}

