#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"


// void	exec_cmds(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
// {
// 	int fd[2];
// 	pid_t pid;
// 	int current_fd;

// 	current_fd = node->in_fd;
// 	while (node)
// 	{
// 		if (node->type == TYPE_OPERATOR && node->weight == OP_PIPE)
// 		{
// 			pipe(fd);
// 			pid = fork();
// 			if (pid == -1)
// 			{
// 				ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
// 				return ;
// 			}
// 			if (pid == 0) // child
// 			{
// 				dup2(current_fd, STDIN_FILENO);
// 				close(fd[0]);
// 				if (!execute_if_builtin(vtr, hashtable, node->left))
// 					execve(node->left->path, node->left->args, NULL);
// 			}
// 			else // parent
// 			{
// 				wait(NULL);
// 				dup2(fd[0], STDIN_FILENO);
// 				close(fd[1]);
// 				if (current_fd != STDIN_FILENO)
// 					close(current_fd);

// 				if (!execute_if_builtin(vtr, hashtable, node->right))
// 					execve(node->right->path, node->right->args, NULL);
// 			}
// 		}
// 		else if (node->type == TYPE_REDIRECT)
// 		{
// 			if (!execute_if_builtin(vtr, hashtable, node))
// 			{
// 				pid = fork();
// 				if (pid == -1)
// 				{
// 					ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
// 					return ;
// 				}
// 				else if (pid == 0)
// 				{
// 					execve(node->path, node->args, NULL);
// 					exit(0);
// 				}
// 				else
// 					wait(NULL);
// 			}
// 		}
// 		else if (node->type == TYPE_COMMAND)
// 		{
// 			if (!execute_if_builtin(vtr, hashtable, node))
// 			{
// 				pid = fork();
// 				if (pid == -1)
// 				{
// 					ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
// 					return ;
// 				}
// 				else if (pid == 0)
// 				{
// 					execve(node->path, node->args, NULL);
// 					exit(0);
// 				}
// 				else
// 					wait(NULL);
// 			}
// 		}
// 		node = node->right;
// 	}
// }

void	exec_cmds(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	int fd[2];
	pid_t pid;
	int current_fd;

	current_fd = node->in_fd;
	if ((node->type == TYPE_OPERATOR && node->weight == OP_PIPE) || (node->type == TYPE_REDIRECT && ft_strcmp(node->cmds, "<<") == 0))
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
			return ;
		}
		if (pid == 0) // child
		{
			dup2(current_fd, STDIN_FILENO);
			close(fd[0]);
			if (!execute_if_builtin(vtr, hashtable, node->left))
				execve(node->left->path, node->left->args, NULL);
			// exit(0);
		}
		else // parent
		{
			wait(NULL);
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			if (current_fd != STDIN_FILENO)
				close(current_fd);
			execve(node->right->path, node->right->args, NULL);
		}
	}

	else if (node->type == TYPE_REDIRECT)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
			return ;
		}
		else if (pid == 0)
		{
			if (!execute_if_builtin(vtr, hashtable, node->left))
				execve(node->left->path, node->left->args, NULL);
			exit(0);
		}
		else
			wait(NULL);
	}
	// else if (node->type == TYPE_COMMAND)
	// {
	// 	if (!execute_if_builtin(vtr, hashtable, node))
	// 	{
	// 		pid = fork();
	// 		if (pid == -1)
	// 		{
	// 			ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
	// 			return ;
	// 		}
	// 		else if (pid == 0)
	// 		{
	// 			// analyzing_cmd(vtr, hashtable, node);
	// 			execve(node->path, node->args, NULL);
	// 			exit(0);
	// 		}
	// 		else
	// 		{
	// 			wait(NULL);
	// 		}
	// 	}
	// }
}