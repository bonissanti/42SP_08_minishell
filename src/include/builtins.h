/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:56:10 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/02 13:07:05 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "./minishell.h"

//############################### Builtins ####################################

void	ft_export(t_hashtable *hashtable, char **args);
void	ft_echo(t_hashtable *hashtable, char **args);
int		ft_exit(char **args);
void	ft_cd(t_hashtable *hashtable, char **args);
void	ft_pwd(t_hashtable *hashtable, char **args);
void	ft_unset(t_hashtable *hashtable, char **args);
void	ft_env(t_hashtable *hashtable, char **args);

//############################### Utils ########################################

void	print_all_env(t_hashtable *hash_table);
void	add_env(t_hashtable *hash_table, char **args);
void	env_with_equals(t_hashtable *hashtable, char **args, int i);
void	env_with_value(t_hashtable *hashtable, t_env *env);
int		valid_identifier_export(char *str);
int		ft_count_args(char **args);

//############################### Free #########################################

void	safe_free(void **ptr);
void	free_split(char **split);
int		ft_count_args(char **args);

#endif