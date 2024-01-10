/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:33:54 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/10 18:32:44 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANERS_H
# define CLEANERS_H

# include "./minishell.h"

void	empty_trash_can(void);
char	*gb_to_free(char *readline_input, t_shell *shell);
void	free_lists(void);
void	final_wipeout(t_hashtable *env);

#endif