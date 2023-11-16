/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:53:13 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/16 17:04:40 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"
#include "../include/builtins.h"

int ft_unset(t_hashtable *hash_table ,char **args)
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
    return (1);
}

