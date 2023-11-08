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
	int num_keys;
	t_hash *buckets[101];
}			t_hashtable;

typedef struct t_env
{
	char *key;
	char **env;
	char *value;
	char **equals_sign;
	int num_env;

}			t_env;

//############################### Hashtable ###################################

t_hashtable		*create_hashtable(void);
unsigned int	hash(char *key);
void			insert(t_hashtable *hash_table, char *key, char *value);
t_hash			*search(t_hashtable *hash_table, char *key);
void			delete_hash(t_hashtable *hash_table, char *key);
void 			destroy_hashtable(t_hashtable *hash_table);

//############################ Hash Utils ###################################

void			bubble_sort(char **array, int size);
int				get_num_keys(t_hashtable *hash_table);
char			**copy_all_keys(t_hashtable *hash_table);
char			*expand_variable(t_hashtable *hash_table, char *arg);
char 	*handle_elements(t_hashtable *hash_table, char *arg);

//############################### Export ######################################

void			init_hash(t_hashtable *hash_table, char **envp);
void			print_all_env(t_hashtable *hash_table);
void			add_env(t_hashtable *hash_table, char **args);
void			ft_export(t_hashtable *hash_table, char **args);

//############################### Echo ########################################

int				ft_echo(t_hashtable *hash_table, char **args);

//############################### Exit ########################################

void	ft_exit(t_hashtable *hash_table, char **args);

//############################### Cd ##########################################

//############################### Pwd #########################################

//############################### Export ######################################

//############################### Unset ########################################

int ft_unset(t_hashtable *hash_table ,char **args);

//############################### Env ##########################################

void ft_env(t_hashtable *hash_table, char **args);
int	ft_count_args(char **args);

//############################### Memory #######################################

void safe_free(void **ptr);
void free_split(char **split);

#endif