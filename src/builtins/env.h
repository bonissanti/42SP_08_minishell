/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:11:30 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/19 18:18:26 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "../../libft/libft.h"

// Hash table size is recommended to be a prime number
# define HASHSIZE 101

typedef struct t_hash
{
	char *key;
	char *value;
	struct t_hash *next;
}			t_hash;	

typedef struct t_hashtable
{
	t_hash *buckets[101];
}			t_hashtable;


//############################### Hashtable ###################################

t_hashtable *create_hashtable(void);
unsigned int hash(char *key);
void insert(t_hashtable *hash_table, char *key, char *value);
t_hash *search(t_hashtable *hash_table, char *key);
void    delete_hash(t_hashtable *hash_table, char *key);

//############################### Export ######################################

void init_hash(t_hashtable *hash_table, char **envp);
void	print_all_env(t_hashtable *hash_table);
void	add_env(t_hashtable *hash_table, char **args);
void	ft_export(t_hashtable *hash_table, char **args);

//############################ Export Utils ###################################

void	bubble_sort(char **array, int size);
int	get_num_keys(t_hashtable *hash_table);
char	**get_all_keys(t_hashtable *hash_table);

#endif