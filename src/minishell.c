/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:38:13 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/14 17:45:39 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_hashtable *hashtable = create_hashtable();
    t_exec exec;

    init_hash(hashtable, envp);
    init_structs(&exec, 0, sizeof(t_exec));;
	prompt(hashtable, exec);
	// backup_fd(&vtr.exec.old_stdin, &vtr.exec.old_stdout);
    // exec_multi_cmds(&vtr, hashtable, root);
    // delete_node(root);
    // destroy_hashtable(hashtable);
}
