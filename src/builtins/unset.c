/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:53:13 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/11 14:43:47 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

