/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:07:07 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 12:50:00 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/hash.h"

void analyze_if_print(t_ast *node, int index)
{
	t_ast *save_node;

	save_node = node->left;
    while (node != NULL)
    {
        if (node->type == TYPE_HEREDOC && index == 0 && (node->right == NULL || node->right->type != TYPE_HEREDOC))
		{
			if (node->left == NULL)
				node->left = save_node;
			node->print_hdoc = true;
		}
		if (node->type == TYPE_REDIRECT && index == 1 && (node->right == NULL || node->right->type != TYPE_REDIRECT))
		{
			if (node->left == NULL)
				node->left = save_node;
			node->print_redir = true;
		}
        node = node->right;
    }
}

void	analyze_cmd(t_hashtable *hashtable, t_ast *node)
{
	char	*path;
	int		result;

	result = verify_cmd_permissions(node->cmds);
	if (ft_strchr(node->cmds, '/') != NULL && result != 0)
	{
		handle_error(node, result);
		return ;
	}
	else if (ft_strchr(node->cmds, '/') != NULL && result == 0)
		node->path = ft_strdup(node->cmds);
	else
	{
		path = search(hashtable, "PATH")->value;
		node->path = build_cmd_path(node, path);
	}
}


void	handle_error(t_ast *node, int result)
{
	if (result == 126)
		ft_fprintf(2, "minishell: %s: command not found\n", node->cmds);
	else if (result == 127)
		ft_fprintf(2, "minishell: %s: %s\n", node->cmds, strerror(errno));
	return ;
}

void	backup_fd(int *old_stdin, int *old_stdout)
{
	*old_stdin = dup(STDIN_FILENO);
	*old_stdout = dup(STDOUT_FILENO);
}

void	restore_fd(int reset_stdin, int reset_stdout)
{
	dup2(reset_stdin, STDIN_FILENO);
	dup2(reset_stdout, STDOUT_FILENO);
	close(reset_stdin);
	close(reset_stdout);
}
