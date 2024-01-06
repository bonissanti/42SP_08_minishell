/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:51:04 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/04 19:01:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirect_input(t_ast *node, char *filename)
{
	if (filename == NULL || isdelimiter(filename))
	{
		if (is_redirect_op(node->right->cmds))
		{
			ft_fprintf(2, "minishell: syntax error near unexpected "
				"token `%s'\n", node->right->cmds);
			return (1);
		}
		else
		{
			ft_fprintf(2, "minishell: syntax error near unexpected token\n");
			return (1);
		}		
	}
	node->in_fd = open(filename, O_RDONLY);
	if (!verify_file_permissions(filename) || node->in_fd == -1)
	{
		node->to_exec = false;
		return (1);
	}
	return (0);
}

int	redirect_output(t_ast *node, char *filename)
{
	if (filename == NULL || isdelimiter(filename))
	{
		if (is_redirect_op(node->right->cmds))
		{
			ft_fprintf(2, "minishell: syntax error near unexpected "
				"token `%s'\n", node->right->cmds);
			return (1);
		}
		else
		{
			ft_fprintf(2, "minishell: syntax error near unexpected "
				"token `%s'\n", filename);
			return (1);
		}
	}
	node->out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!verify_file_permissions(filename))
	{
		node->to_exec = false;
		return (1);
	}
	return (0);
}

int	redirect_append(t_ast *node, char *filename)
{
	if (filename == NULL || isdelimiter(filename))
	{
		if (is_redirect_op(node->right->cmds))
		{
			ft_fprintf(2, "minishell: syntax error near unexpected "
				"token `%s'\n", node->right->cmds);
			return (1);
		}
		else
		{
			ft_fprintf(2, "minishell: syntax error near unexpected "
				"token `%s'\n", filename);
			return (1);
		}
	}
	node->out_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!verify_file_permissions(filename))
	{
		node->to_exec = false;
		return (1);
	}
	return (0);
}

static int	handle_options(t_exec *exec, t_ast *node, int option)
{
	int		ok_to_create;

	ok_to_create = 0;
	if (option == 0 && exec->error_call != 1)
	{
		ok_to_create = handle_redirects(node);
		if ((ok_to_create == 1 || ok_to_create == -1) && (option == 1))
			return (1);
	}
	if (option == 1)
		redirect_fds(node);
	return (ok_to_create);
}

int	create_files(t_ast *node, t_exec *exec, int option)
{
	t_ast	*root;
	int		ok_to_create;

	root = node;
	ok_to_create = 0;
	while (root || root == node)
	{
		if (exec->error_call == 1 && exec->count_pipes == 0)
			return (1);
		if (root->type == TYPE_REDIRECT)
		{
			ok_to_create = handle_options(exec, root, option);
			if (ok_to_create == 1)
				return (1);
		}
		if (root)
			root = root->right;
		else
			return (1);
	}
	return (ok_to_create);
}
