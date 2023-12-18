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

#ifndef HASH_H
# define HASH_H

# include "./minishell.h"

// Hash table size is recommended to be a prime number
# define HASHSIZE 101

//############################### Hashtable ###################################

t_hashtable		*create_hashtable(void);
unsigned int	hash(char *key);
void			insert(t_hashtable *hash_table, char *key, char *value);
t_hash			*search(t_hashtable *hash_table, char *key);
void			delete_hash(t_hashtable *hash_table, char *key);
void			destroy_hashtable(t_hashtable *hash_table);

//############################ Hash Utils ###################################

void			bubble_sort(char **array, int size);
int				get_num_keys(t_hashtable *hash_table);
void			handle_value(t_hash *check_dup, char *value, char *value_copy);
void			add_new_key(t_hashtable *hash, char *key_copy, char *value_copy,
					size_t index);
char			**copy_all_keys(t_hashtable *hash_table);
char			*handle_elements(t_hashtable *hash_table, char *arg);
void			init_hash(char **envp);

#endif