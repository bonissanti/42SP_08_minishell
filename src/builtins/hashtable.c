#include "env.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function: Create_hashtable
 * -----------------
 * This function will allocate memory for the buckets of the hashtable.
 * For default, buckets will be 101 and must be initialized to 0.
 * 
 * @var: hash_table: Pointer to the hashtable.
 * 
 * @return: Returns the pointer to the hashtable.
 *
 */

t_hashtable *create_hashtable(void)
{
    t_hashtable *hash_table;

    hash_table = (t_hashtable *)calloc(1, sizeof(t_hashtable));
    return (hash_table);
}

/**
 * Function: Hash
 * -----------------
 * This function is used to determine the index of the bucket where the
 * key-value pair will be stored. It uses the multiplicative shift hash
 * method. Basically, based on the ASCII value of the key, it will
 * bitshift the value 5 times to the left and add the ASCII value of the
 * next character of the key. This will be done until the end of the key.
 * After that, it will use the modulo operator to get the remainder of the
 * division of the hash by the size(101) of the hashtable.
 *  
 * @param: key: The environment variable name.
 * @var: hash: The hash value, which will be the index of the bucket.
 * 
 * @return: Returns the index of the bucket.
 *
 */

unsigned int hash(char *key)
{
    unsigned int hash;

    hash = 0;
    while (*key)
            hash = (hash << 5) + *key++;
    return (hash % HASHSIZE);
}

/**
 * Function: Insert
 * -----------------
 * This function is used to add the environment variable to the hashtable.
 * After get index of the bucket, it will allocate memory for the new
 * environment variable and pass the key and value to the new environment.
 *  
 * @param: hash_table: The pointer to the hashtable.
 * @param: key: The environment variable name.
 * @param: value: The environment variable value.
 * 
 * @var: index: The index of the bucket.
 * @var: add_env: The new environment variable to be added.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */

void insert(t_hashtable *hash_table, char *key, char *value)
{
    unsigned int index;
    t_hash *add_env;
    t_hash *check_dup;
    char *key_copy;

    index = hash(key);
    key_copy = strdup(key);
    check_dup = search(hash_table, key_copy);
    if (check_dup != NULL)
    {
        free(check_dup->value);
        check_dup->value = strdup(value);
        return ;
    }
    else
    {
        add_env = (t_hash *)malloc(sizeof(t_hash));
    
        add_env->key = key_copy;
        add_env->value = value; // if broken, try strdup for value

        add_env->next = hash_table->buckets[index];
        hash_table->buckets[index] = add_env;
    }
    
}

/**
 * Function: Search
 * -----------------
 * This function is used to search for an environment variable in the
 * hashtable. After knowing the index of the bucket, it will iterate
 * through the hashtable until it finds the environment variable.
 * If it finds it, it will return the value of the environment variable.
 * If it does not find it, it will return NULL.
 *  
 * @param: hash_table: The pointer to the hashtable.
 * @param: key: The environment variable name.
 * 
 * @var: index: The index of the bucket.
 * @var: search_env: The environment variable to be searched.
 * 
 * @return: Returns pointer to the value of the environment variable.
 *
 */

t_hash *search(t_hashtable *hash_table, char *key)
{
    unsigned int index;
    t_hash *search_env;

    index = hash(key);
    search_env = hash_table->buckets[index];
    while (search_env != NULL)
    {
        if (strcmp(search_env->key, key) == 0)
            return (search_env);
        search_env = search_env->next;
    }
    return (NULL);
}

/**
 * Function: Delete
 * -----------------
 * This function is used to search for an environment variable in the
 * hashtable. After knowing the index of the bucket, it will iterate
 * through the hashtable until it finds the environment variable.
 * If it finds it, it will return the value of the environment variable.
 * If it does not find it, it will return NULL.
 *  
 * @param: hash_table: The pointer to the hashtable.
 * @param: key: The environment variable name.
 * 
 * @var: index: The index of the bucket.
 * @var: search_env: The environment variable to be searched.
 * 
 * @return: Returns pointer to the value of the environment variable.
 *
 */


void    delete_hash(t_hashtable *hash_table, char *key)
{
    unsigned int index;
    t_hash *delete_env;
    t_hash *prev_env;

    index = hash(key);
    delete_env = hash_table->buckets[index];
    prev_env = NULL;

    while (delete_env != NULL)
    {
        if (strcmp(delete_env->key, key) == 0)
        {
            if (prev_env == NULL)
                hash_table->buckets[index] = delete_env->next;
            else
                prev_env->next = delete_env->next;
            free(delete_env);
            return ;
        }
        prev_env = delete_env;
        delete_env = delete_env->next;
    }
}

// int main(void)
// {
//     t_hashtable *hash_table = create_hashtable();

//     insert(hash_table, "PATH", "/usr/bin:bin");
//     insert(hash_table, "HOME", "/home/user");
//     insert(hash_table, "USER", "user");

//     printf("%s\n", search(hash_table, "PATH"));
//     printf("%s\n", search(hash_table, "HOME"));
//     printf("%s\n", search(hash_table, "USER"));

//     delete(hash_table, "PATH");
//     delete(hash_table, "HOME");
//     delete(hash_table, "USER");

//     // printf("%s\n", search(hash_table, "PATH"));

//     free(hash_table);

//     return (0);

// }