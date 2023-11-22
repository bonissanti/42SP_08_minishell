/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:07:07 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/22 19:43:06 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/temp_ast.h"
#include "../include/builtins.h"
#include "../include/hash.h"

void	analyzing_cmd(t_hashtable *hashtable, t_temp_ast *node)
{
	char *path;
	
	if (node)
	{
		if (node->type == TYPE_COMMAND)
		{
			path = search(hashtable, "PATH")->value;
			build_cmd_path(path);
		}
		else if (node->type == TYPE_REDIRECT && ft_strncmp(node->args, "<<", 2) == 0)
			handle_heredoc(hashtable, node->delim);
		else if (node->type == TYPE_REDIRECT && node->args == '<')
			redirect_input(node->infile);
		else if (node->type == TYPE_REDIRECT && node->args == '>')
			redirect_output(node->outfile);
		else if (node->type == TYPE_REDIRECT && node->args == '>>')
			redirect_append(node->outfile);
	}
}

