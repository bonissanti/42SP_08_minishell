/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:42:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/13 17:49:18 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_exec_vector(t_vector *vtr)
{
	init_structs(&vtr->exec, 0, sizeof(t_exec));
}

void    init_cmd(t_vector *vtr)
{
    vtr->builtins[0].cmd = NULL;
    vtr->builtins[0].name = "echo";
    vtr->builtins[0].function = ft_echo;
    vtr->builtins[1].cmd = NULL;
    vtr->builtins[1].name = "cd";
    vtr->builtins[1].function = ft_cd;
    vtr->builtins[2].cmd = NULL;
    vtr->builtins[2].name = "pwd";
    vtr->builtins[2].function = ft_pwd;
    vtr->builtins[3].cmd = NULL;
    vtr->builtins[3].name = "export";
    vtr->builtins[3].function = ft_export;
    vtr->builtins[4].cmd = NULL;
    vtr->builtins[4].name = "unset";
    vtr->builtins[4].function = ft_unset;
    vtr->builtins[5].cmd = NULL;
    vtr->builtins[5].name = "env";
    vtr->builtins[5].function = ft_env;
    vtr->builtins[5].cmd = NULL;
    vtr->builtins[5].name = "exit";
    vtr->builtins[5].function = ft_exit;
    vtr->builtins[6].cmd = NULL;
    vtr->builtins[6].name = NULL;
    vtr->builtins[6].function = NULL;
}

void	init_redirects(t_vector *vtr)
{
	vtr->redirect[0].name = "<";
	vtr->redirect[1].name = ">";
	vtr->redirect[2].name = ">>";
	vtr->redirect[3].name = NULL;
	vtr->redirect[0].function = redirect_input;
	vtr->redirect[1].function = redirect_output;
	vtr->redirect[2].function = redirect_append;
	vtr->redirect[3].function = NULL;
}
