/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:43:27 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/13 17:59:42 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/segments.h"

static void	redirect_fds(t_ast *node, int *prev_pipe);
static void	check_pipe(t_vector *vtr, t_hashtable *hashtable, t_ast *node,
				int *next_pipe);
static void	child_redirect(t_vector *vtr, t_hashtable *hashtable, t_ast *node,
				int *next_pipe);

void	handle_redirects(t_vector *vtr, t_ast *node)
{
	if (node->type == TYPE_REDIRECT)
	{
		if (ft_strncmp(node->cmds, ">", 1) == 0)
			redirect_output(node, node->delim);
		else if (ft_strncmp(node->cmds, ">>", 2) == 0)
			redirect_append(node, node->delim);
		else if (ft_strncmp(node->cmds, "<", 1) == 0)
			redirect_input(node, node->delim);
	}
}

void	analyze_redirect(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{		
	if (node->type == TYPE_REDIRECT)
	{
    	// analyze_if_print(node, 1);
		if (ft_strncmp(node->cmds, ">", 1) == 0 || ft_strncmp(node->cmds, ">>", 2) == 0)
			simple_redirect_out(vtr, hashtable, node, NULL);
		else
			simple_redirect_in(vtr, hashtable, node);
	}
}




static void	check_pipe(t_vector *vtr, t_hashtable *hashtable, t_ast *node,
		int *next_pipe)
{
	if (vtr->exec.count_pipes >= 1)
	{
		vtr->exec.count_pipes--;
		close(next_pipe[1]);
		pipe_from_redirect(hashtable, vtr, node->right, next_pipe);
	}
}
