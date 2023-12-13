/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:43:27 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/13 18:22:39 by brunrodr         ###   ########.fr       */
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
    analyze_if_print(node, 1);
	if (node->type == TYPE_REDIRECT && node->print_redir == true)
	{
		if (ft_strncmp(node->cmds, ">", 1) == 0 || ft_strncmp(node->cmds, ">>", 2) == 0)
			simple_redirect_out(vtr, hashtable, node, NULL);
		else
			simple_redirect_in(vtr, hashtable, node);
	}
}
