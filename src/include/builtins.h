/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:56:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 12:33:34 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../include/hash.h"
# include <errno.h>

typedef struct t_env
{
	char	*key;
	char	**env;
	char	*value;
	char	**equals_sign;
	int		num_env;
}			t_env;

typedef struct s_command
{
	char	*name;
	void	(*function)(char *args);
}		t_command;

//############################### Builtins ####################################

void		ft_export(t_hashtable *hash_table, char **args);
int			ft_echo(t_hashtable *hash_table, char **args);
void		ft_exit(t_hashtable *hash_table, char **args);
int			ft_cd(t_hashtable *hashtable, char **args);
void		ft_pwd(t_hashtable *hashtable, char **args);
int			ft_unset(t_hashtable *hash_table, char **args);
void		ft_env(t_hashtable *hash_table, char **args);

//############################### Vector ######################################

// void		execute_builtins(t_pointer *builtins, t_hashtable *hash_table, char **args);
void		is_cd(void);
void		is_pwd(void);
void		is_echo(void);
void		is_export(void);
void		is_unset(void);
void		is_env(void);
void		is_exit(void);

//############################### Utils ########################################

void		print_all_env(t_hashtable *hash_table);
void		add_env(t_hashtable *hash_table, char **args);
void	    env_with_equals(t_hashtable *hashtable, char **args, int i);
void		env_with_value(t_hashtable *hashtable, char **args, int i, size_t len);
int			ft_count_args(char **args);

//############################### Free #########################################

void		safe_free(void **ptr);
void		free_split(char **split);
int			ft_count_args(char **args);

#endif