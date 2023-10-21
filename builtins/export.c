#include "env.h"
#include <stdio.h>

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