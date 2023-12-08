/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:42:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/06 17:27:05 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/segments.h"

void	init_exec_vector(t_vector *vtr)
{
	init_structs(&vtr->exec, 0, sizeof(t_exec));
	init_cmd(vtr);
	init_redirects(vtr);
}

void	init_cmd(t_vector *vtr)
{
	vtr->builtins[0].cmd = NULL;
	vtr->builtins[0].name = "echo";
	vtr->builtins[0].function = ft_echo;
	vtr->builtins[1].name = NULL;
	vtr->builtins[1].function = NULL;
}

void    init_redirects(t_vector *vtr)
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

