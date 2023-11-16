#ifndef BUILTINS_H
# define BUILTINS_H

# include "../include/env.h"
# include <errno.h>

//############################### Export ######################################

void		ft_export(t_hashtable *hash_table, char **args);
void		print_all_env(t_hashtable *hash_table);
void		add_env(t_hashtable *hash_table, char **args);
void	    env_with_equals(t_hashtable *hashtable, char **args, int i);
void		env_with_value(t_hashtable *hashtable, char **args, int i, size_t len);

//############################### Echo ########################################

int			ft_echo(t_hashtable *hash_table, char **args);

//############################### Exit ########################################

void		ft_exit(t_hashtable *hash_table, char **args);

//############################### Cd ##########################################

int			ft_cd(t_hashtable *hashtable, char **args);

//############################### Pwd #########################################

void		ft_pwd(void);

//############################### Unset ########################################

int			ft_unset(t_hashtable *hash_table, char **args);

//############################### Env ##########################################

void		ft_env(t_hashtable *hash_table, char **args);
int			ft_count_args(char **args);

//############################### Utils ########################################

void		safe_free(void **ptr);
void		free_split(char **split);
int			ft_count_args(char **args);

#endif