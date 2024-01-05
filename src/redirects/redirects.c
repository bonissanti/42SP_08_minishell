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

// int	create_temp_file(t_ast *node, char *filename)
// {
// 	int		tmp_fd;
// 	char	*tmp_filename;

// 	(void)node;
// 	tmp_filename = "/tmp/minishell_tmp_file";
// 	tmp_fd = open(tmp_filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	if (tmp_fd != -1)
// 	{
// 		close(tmp_fd);
// 		ft_fprintf(2, "minishell: %s: %s\n", filename, strerror(errno));
// 		tmp_fd = open(tmp_filename, O_RDONLY);
// 		unlink(tmp_filename);
// 	}	
// 	return (1);
// }

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

int	create_files(t_ast *node, t_exec *exec, int option)
{
	t_ast	*root;

	root = node;

	while (root || root == node)
	{
        if (exec->error_call == 1 && exec->count_pipes == 0)
            return (1);
		if (root->type == TYPE_REDIRECT)
		{
			if (option == 0 && exec->error_call != 1)
			{
				exec->error_call = handle_redirects(root);
				if ((exec->error_call == 1 || exec->error_call == -1) && (option == 1))
					return (1);
			}
			if (option == 1)
				redirect_fds(root);
		}
		if (root)
			root = root->right;
		else
			return (1);
	}
	return (0);
}
