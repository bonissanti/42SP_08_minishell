#ifndef BUILTINS_H
# define BUILTINS_H

#include <errno.h>
#include "env.h"

typedef struct t_env
{
	char *key;
	char **env;
	char *value;
	char **equals_sign;
	int num_env;

}			t_env;

//############################### Export ######################################

void			ft_export(t_hashtable *hash_table, char **args);
void			print_all_env(t_hashtable *hash_table);
void			add_env(t_hashtable *hash_table, char **args);

//############################### Echo ########################################

int				ft_echo(t_hashtable *hash_table, char **args);

//############################### Exit ########################################

void	ft_exit(t_hashtable *hash_table, char **args);

//############################### Cd ##########################################

int	ft_cd(t_hashtable *hashtable, char **args);

//############################### Pwd #########################################

void	ft_pwd(void);

//############################### Unset ########################################

int ft_unset(t_hashtable *hash_table ,char **args);

//############################### Env ##########################################

void ft_env(t_hashtable *hash_table, char **args);
int	ft_count_args(char **args);

//############################### Memory #######################################

void safe_free(void **ptr);
void free_split(char **split);

#endif