/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:56:10 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/11 12:15:33 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "./minishell.h"

//############################### Builtins ####################################

void	ft_export(t_shell *shell, char **args);
void	ft_echo(t_shell *shell, char **args);
int		ft_exit(t_shell *shell, char **args);
void	ft_cd(t_shell *shell, char **args);
void	ft_pwd(t_shell *shell, char **args);
void	ft_unset(t_shell *shell, char **args);
void	ft_env(t_shell *shell, char **args);

//############################### Utils ########################################

void	print_all_env(t_hashtable *hash_table);
void	add_env(t_shell *shell, char **args);
void	env_with_equals(t_shell *shell, char **args, int i);
void	env_with_value(t_hashtable *hashtable, t_env *env);
int		valid_identifier_export(char *str);
int		ft_count_args(char **args);

//############################### Free #########################################

void	safe_free(void **ptr);
void	free_split(char **split);
int		ft_count_args(char **args);

#endif