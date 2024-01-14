/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:33:54 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/13 21:51:48 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANERS_H
# define CLEANERS_H

# include "./minishell.h"

void	empty_trash_can(void);
char	*gb_to_free(void *readline_input, t_shell *shell);
void	free_lists(void);
void	final_wipeout(t_hashtable *env);
void	free_envp(char **envp);
char	**matrix_to_free(char **matrix);

#endif