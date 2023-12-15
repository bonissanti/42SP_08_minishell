/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:38:13 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/15 17:07:04 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    t_exec exec;

    init_hash(envp);
    init_structs(&exec, 0, sizeof(t_exec));
	prompt(g_global.hash, exec);
	// backup_fd(&vtr.exec.old_stdin, &vtr.exec.old_stdout);
    // exec_multi_cmds(&vtr, hashtable, root);
    // delete_node(root);
    // destroy_hashtable(hashtable);
}
