/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:56:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 13:06:39 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../include/hash.h"
# include "../include/ast.h"
# include <errno.h>
#include "../../libft/libft.h"

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
	void	(*function)(t_hashtable *hash_table, char **args);
}		t_command;

//############################### Builtins ####################################

void		init_builtins(t_command *cmd);
void		is_builtins(t_command *builtins, t_hashtable *hashtable, t_ast *node);
// void		ft_export(t_hashtable *hashtable, char **args);
void 		ft_echo(t_hashtable *hashtable, char **args);
// void		ft_exit(t_hashtable *hashtable, char **args);
// void		ft_cd(t_hashtable *hashtable, char **args);
// void		ft_pwd(t_hashtable *hashtable, char **args);
// void 		ft_unset(t_hashtable *hashtable ,char **args);
// void		ft_env(t_hashtable *hashtable, char **args);

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