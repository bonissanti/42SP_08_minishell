#include <stdlib.h>
#include <stdio.h>
#include "../include/env.h"

void ft_env(t_hashtable *hash_table, char **args)
{
    int i;
    char **keys;
    char *value;
    int argc;

    i = -1;
    argc = ft_count_args(args);
    keys = copy_all_keys(hash_table);
    if (argc > 1) //refatorar criando ft_fprintf
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        exit(127);
    }
    while (++i < hash_table->num_keys)
    {
        value = search(hash_table, keys[i])->value;
        if (value != NULL)
            printf("%s=%s\n", keys[i], value);
    }
    free(keys);
}