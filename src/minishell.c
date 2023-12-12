/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:38:13 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/12 16:14:14 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_hashtable *hashtable = create_hashtable();
    t_vector vtr;

    init_hash(hashtable, envp);
    init_exec_vector(&vtr);
	prompt(hashtable, vtr);
	// backup_fd(&vtr.exec.old_stdin, &vtr.exec.old_stdout);
    // exec_multi_cmds(&vtr, hashtable, root);
    // delete_node(root);
    // destroy_hashtable(hashtable);
}
