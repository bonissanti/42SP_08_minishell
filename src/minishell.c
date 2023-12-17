/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:38:13 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/15 20:01:43 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    t_exec exec;

    init_hash(envp);
	prompt(g_global.hash, exec);
	// backup_fd(&vtr.exec.old_stdin, &vtr.exec.old_stdout);
    // exec_multi_cmds(&vtr, hashtable, root);
    // delete_node(root);
    // destroy_hashtable(hashtable);
    return (g_global.exit_status);
}
