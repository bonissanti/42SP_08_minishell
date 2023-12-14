/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:39:43 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/14 17:31:20 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "./structs.h"
#include "./segments.h"
#include "./parser.h"
#include "./ast.h"
#include "./hash.h"
#include "./exec.h"
#include "./builtins.h"

extern t_global g_global;

void 	prompt(t_hashtable *env, t_exec exec);

#endif