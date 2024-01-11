/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:33:54 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/11 12:16:49 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANERS_H
# define CLEANERS_H

# include "./minishell.h"

void	empty_trash_can(void);
char	*gb_to_free(char *readline_input, t_shell *shell);
void	free_lists(void);
void	final_wipeout(t_hashtable *env);
void	free_envp(char **envp);

#endif