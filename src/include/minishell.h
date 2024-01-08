/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:39:43 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/08 18:18:19 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "./structs.h"
# include "./segments.h"
# include "./parser.h"
# include "./ast.h"
# include "./hash.h"
# include "./exec.h"
# include "./builtins.h"
# include "./signals.h"
# include "./cleaners.h"

extern t_global	g_global;

void	prompt(t_hashtable *env);

#endif