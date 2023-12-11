/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:39:43 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/10 19:52:30 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "src/include/structs.h"
#include "src/include/parser.h"
#include "src/include/ast.h"
#include "src/include/hash.h"
#include "src/include/exec.h"
#include "src/include/builtins.h"
#include "src/include/segments.h"

extern t_global g_global;

void		prompt(t_hashtable *env);

#endif