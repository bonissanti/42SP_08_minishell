/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:02:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/15 20:02:47 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void open_execute(t_hashtable *hash, t_exec *exec, t_ast *node, char *filename);

// static char *generate_filename(int count_hdoc)
// {
// 	char *template;
// 	char *count_str;
// 	char *filename;
	
// 	template = "/tmp/heredocXXX-";
// 	count_str = ft_itoa(count_hdoc);
// 	filename = ft_strjoin(template, count_str);

// 	free(count_str);
// 	return (filename);
// }

// static void test_looping(t_hashtable *hash, t_exec *exec, t_ast *node)
// {
// 	char *line;
// 	char *filename;

// 	filename = generate_filename(exec->count_hdoc);
// 	node->out_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!ft_strcmp(line, "exit"))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (node->print_hdoc)
// 			ft_putendl_fd(line, node->out_fd);
// 		free(line);
// 	}
// 	close(node->out_fd);
// 	if (node->print_hdoc)
// 		open_execute(hash, exec, node, filename);
// }

// static void open_execute(t_hashtable *hash, t_exec *exec, t_ast *node, char *filename)
// {
	
// 	analyze_cmd(hash, node->left);
// 	node->pid = fork();
// 	if (node->pid == 0)
// 	{
// 		node->in_fd = open(filename, O_RDONLY);
// 		dup2(node->in_fd, STDIN_FILENO);
// 		close(node->in_fd);
// 		execve(node->left->path, node->left->args, NULL);
// 		exit(0);
// 	}
// 	else
// 		wait(NULL);
// }

// static t_bool valid_node(t_ast *node)
// {
// 	if ((node->type == TYPE_COMMAND || node->type == TYPE_REDIRECT || node->type == TYPE_PIPE 
// 		|| node->type == TYPE_HEREDOC || node->type == TYPE_LOGICAL)
// 		&& (node->left == NULL && node->right == NULL))
// 	{
// 		g_global.cmd_status = 2;
// 		return (true);
// 	}
// 	return (false);
// }

int	exec_multi_cmds(t_exec *exec, t_hashtable *hashtable, t_ast *root)
{
	int	initial_pipe[2];

	initial_pipe[0] = -1;
	initial_pipe[1] = -1;
	if (root == NULL)
		return (0);

	if (root->type == TYPE_COMMAND)
		exec_forked_cmd(hashtable, root);
	if (root->type == TYPE_REDIRECT)
	{
		handle_redirects(root);
		analyze_redirect(exec, hashtable, root);
	}
	if (root->type == TYPE_HEREDOC)
		analyze_heredoc(exec, root, hashtable);
	if (root->type == TYPE_PIPE)
	{
		handle_pipes(hashtable, exec, root, initial_pipe);
		restore_fd(exec->old_stdin, exec->old_stdout);
	}
	if (root->type == TYPE_LOGICAL)
	{
		handle_logical(exec, hashtable, root);
		restore_fd(exec->old_stdin, exec->old_stdout);
	}
	return (g_global.exit_status);
}

void    wait_for_children(t_ast *node)
{
    int status;

    status = 0;
    if (node == NULL)
        return ;

    if (node->type == TYPE_REDIRECT || node->type == TYPE_COMMAND || node->type == TYPE_PIPE ||  node->type == TYPE_HEREDOC)
    {
        waitpid(node->pid, &status, 0);
        if (WIFEXITED(status))
            g_global.cmd_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_global.cmd_status = WTERMSIG(status);
    }
    else if (node->right)
        wait_for_children(node->right);
}

int	exec_forked_cmd(t_hashtable *hash, t_ast *node)
{
	if (!analyze_cmd(hash, node))
		return (g_global.cmd_status);
	if (is_builtin(node))
		execute_builtin(hash, node);
	else
		g_global.cmd_status = forking(node);
	
	return (g_global.exit_status);
}

int	forking(t_ast *node)
{
	node->pid = fork();
	if (node->type == TYPE_COMMAND)
	{
		if (node->pid == 0)
		{
			g_global.cmd_status = execve(node->path, node->args, NULL);
			exit(g_global.cmd_status);
		}
		else
			wait_for_children(node);
	}
	return (g_global.cmd_status);
}