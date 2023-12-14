/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:56:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/13 19:08:50 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "./minishell.h"

//############################### Builtins ####################################

int		ft_export(t_hashtable *hashtable, char **args);
int 		ft_echo(t_hashtable *hashtable, char **args);
void		ft_exit(t_hashtable *hashtable, char **args);
int		ft_cd(t_hashtable *hashtable, char **args);
int		ft_pwd(t_hashtable *hashtable, char **args);
int 		ft_unset(t_hashtable *hashtable ,char **args);
int		ft_env(t_hashtable *hashtable, char **args);

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