/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:24:59 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/24 19:34:23 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>


void	init_env(t_hashtable *hashtable, char **envp)
{
	char *key;
	char *value;
	char *equals_sign;
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		equals_sign = ft_strchr(envp[i], '=');
		key = envp[i];
		value = equals_sign + 1;
		*equals_sign = '\0';
		insert(hashtable, key, value);
	}
}

int get_num_keys(t_hashtable *hash_table)
{
    int i;
    int num_keys;
    t_hash *current;

    i = -1;
    num_keys = 0;
    while (++i < HASHSIZE)
    {
        current = hash_table->buckets[i];
        while (current != NULL)
        {
            num_keys++;
            current = current->next;
        }
    }
    return (num_keys);
}

char **get_all_keys(t_hashtable *hash_table)
{
    t_hash *current;
    char **keys;
    int num_keys;
    int i;

    i = -1;
    num_keys = get_num_keys(hash_table);
    keys = (char **)malloc(sizeof(char *) * num_keys);
    while (++i < HASHSIZE)
    {
        current = hash_table->buckets[i];
        while (current != NULL)
        {
            keys[i] = current->key;
            current = current->next;
        }
    }
    return (keys);
}

/**
 * Function: Export
 * -----------------
 * This function is currently divided into two parts. At the start,
 * the function checks if there are any arguments. If there are no
 * arguments, the function prints (almost) all the environment variables.
 * If there are arguments, the function will iterate through the arguments
 * and add them to the hashtable.
 * 
 * @param: hash_table: The pointer to the hashtable.
 * @param: args: The arguments passed to the function.
 * 
 * @var: hash: The pointer to the hash node.
 * @var: name: The name of the environment variable.
 * @var: value: The value of the environment variable.
 * 
 * @return: Returns 1 if the function was successful.
 *
 */

int ft_export(t_hashtable *hash_table, char **args)
{
    t_hash *hash;
    char *name;
    char *value;
    int     i;

    i = -1;
    if (args[1] == NULL)
    {
        while (++i < HASHSIZE)
        {
            hash = hash_table->buckets[i];
            while (hash != NULL)
            {
                printf("%s=%s\n", hash->key, hash->value);
                hash = hash->next;
            }
        }
    }
    else
    {
        i = 1;
        while (args[i] != NULL)
        {
            name = args[i];
            value = args[i + 1];
            if (value == NULL)
                value = "";
            insert(hash_table, name, value);
            i += 2;
        }
    }
    return (1);
}

int main(void)
{
    t_hashtable *hash_table = create_hashtable();

    char *args[] = {"export", "PATH", "/usr/bin:bin", "HOME", "/home/user", "USER", "user", NULL};
    ft_export(hash_table, args);

    char *args2[] = {"export", NULL};
    ft_export(hash_table, args2);

    delete_hash(hash_table, "PATH");
    delete_hash(hash_table, "HOME");
    delete_hash(hash_table, "USER");

    free(hash_table);

    return (0);
}