/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:51:04 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/28 19:18:59 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_temp_file(t_ast *node, char *filename)
{
	int		tmp_fd;
	char	*tmp_filename;

	tmp_filename = "/tmp/minishell_tmp_file";
	tmp_fd = open(tmp_filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (tmp_fd != -1)
	{
		close(tmp_fd);
		ft_fprintf(2, "minishell: %s: %s\n", filename, strerror(errno));
		node->in_fd = open(tmp_filename, O_RDONLY);
		unlink(tmp_filename);
	}	
	return (-1);
}

int	redirect_input(t_ast *node, char *filename)
{
	if (filename == NULL || isdelimiter(filename))
	{
		if (is_redirect_op(node->right->cmds))
		{
			ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n"
				, node->right->cmds);
			return (1);
		}
		else
		{
			ft_fprintf(2, "minishell: syntax error near unexpected token\n");
			return (1);
		}		
	}
	node->in_fd = open(filename, O_RDONLY);
	if (node->in_fd == -1 || !verify_file_permissions(filename))
		return (create_temp_file(node, filename));
	return (0);
}

int	redirect_output(t_ast *node, char *filename)
{
	if (filename == NULL || isdelimiter(filename))
	{
		if (is_redirect_op(node->right->cmds))
		{
			ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n"
				, node->right->cmds);
			return (1);
		}
		else
		{
			ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n"
				, filename);
			return (1);
		}
	}
	node->out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!verify_file_permissions(filename))
		return (1);
	return (0);
}

int	redirect_append(t_ast *node, char *filename)
{
	if (filename == NULL || isdelimiter(filename))
	{
		if (is_redirect_op(node->right->cmds))
		{
			ft_fprintf(2, "minishell: syntax error near unexpected \
				token `%s'\n", node->right->cmds);
			return (1);
		}
		else
		{
			ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n"
				, filename);
			return (1);
		}
	}
	node->out_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!verify_file_permissions(filename))
		return (1);
	return (0);
}

int	create_files(t_ast *node, t_exec *exec)
{
	static t_ast	*root;
	int				ok_to_create;

	root = node;
	ok_to_create = 1;
	while (root)
	{
		if (root->type == TYPE_REDIRECT)
		{
			ok_to_create = handle_redirects(root);
			if (ok_to_create == 1 || ok_to_create == -1)
			{
				free_for_finish(exec, g_global.hash);
				return (1);
			}
			redirect_fds(root);
		}
		else if (ok_to_create == 0)
			root = root->right;
		else
			return (1);
		if (root)
			root = root->right;
	}
	return (0);
}
