/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:33:54 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/19 12:33:55 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANERS_H
# define CLEANERS_H

# include "./minishell.h"

void	empty_trash_can(void);
char	*readline_trash_can(char *readline_input);
void	free_lists(void);
void	final_wipeout(t_hashtable *env);

#endif