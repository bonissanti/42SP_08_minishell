#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"

void	simple_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node);
void	execute_and_or(t_vector  *vtr, t_hashtable *hashtable, t_ast *node);

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

// void	exec_cmds(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
// {
// 	int fd[2];
// 	pid_t pid;
// 	int current_fd;

// 	current_fd = node->in_fd;
// 	if ((node->type == TYPE_OPERATOR && node->weight == OP_PIPE) || (node->type == TYPE_REDIRECT))
// 	{
// 		pipe(fd);
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
// 			return ;
// 		}
// 		if (pid == 0) // child
// 		{
// 			dup2(current_fd, STDIN_FILENO);
// 			close(fd[0]);
// 			if (!execute_if_builtin(vtr, hashtable, node->left) && node->left->type == TYPE_COMMAND)
// 				execve(node->left->path, node->left->args, NULL);
// 			// exit(0);
// 		}
// 		else // parent
// 		{
// 			wait(NULL);
// 			dup2(fd[0], STDIN_FILENO);
// 			close(fd[1]);
// 			if (current_fd != STDIN_FILENO)
// 				close(current_fd);
// 			// if (!execute_if_builtin(vtr, hashtable, node->right) && node->right->type == TYPE_COMMAND)
// 				// execve(node->right->path, node->right->args, NULL);
// 		}
// 	}
// 	else if (node->type == TYPE_REDIRECT)
// 		simple_execution(vtr, hashtable, node->left);
// 	else if (node->type == TYPE_COMMAND)
// 		simple_execution(vtr, hashtable, node);
// }



// funciona com multiplos pipes

// void	handle_cmd(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
// {
// 	int	fd[2];
// 	pid_t pid;
// 	int current_fd;

// 	if (node == NULL)
// 		return ;
	
// 	current_fd = node->in_fd;
// 	if ((node->type == TYPE_OPERATOR && ft_strcmp(node->cmds, "|") == 0 )||(node->type == TYPE_REDIRECT))
// 	{
// 		pipe(fd);
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
// 			return ;
// 		}
// 		if (pid == 0)
// 		{
// 			close(fd[0]);
// 			if (current_fd != STDIN_FILENO)
// 			{
// 				dup2(current_fd, STDIN_FILENO);
// 				close(current_fd);
// 			}
// 			// else if (node->type != TYPE_REDIRECT)
// 			dup2(fd[1], STDOUT_FILENO);
// 			if (!execute_if_builtin(vtr, hashtable, node->left))
// 				execve(node->left->path, node->left->args, NULL);
// 			exit(0);
// 		}
// 		else
// 		{
// 			wait(NULL);
// 			dup2(fd[0], STDIN_FILENO);
// 			ft_fprintf(2, "fd[0]: %d\n", fd[0]);
// 			close(fd[1]);
// 			if (current_fd != STDIN_FILENO)
// 				close(current_fd);
// 			if (!execute_if_builtin(vtr, hashtable, node->right))
// 				execve(node->right->path, node->right->args, NULL);
// 		}
// 	}
	
// 	else if (node->type == TYPE_OPERATOR && ft_strcmp(node->cmds, "|" ) != 0)
// 		execute_and_or(vtr, hashtable, node);
// 	else if (node->type == TYPE_REDIRECT && node->left->type == TYPE_COMMAND)
// 		simple_execution(vtr, hashtable, node->left);
// 	else if (node->type == TYPE_COMMAND && node->left == NULL && node->right == NULL)
// 		simple_execution(vtr, hashtable, node);

// 	if (node->right)
// 		handle_cmd(vtr, hashtable, node->right);
// }


void	execute_and_or(t_vector  *vtr, t_hashtable *hashtable, t_ast *node)
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
		return ;
	}
	if (pid == 0)
	{
		if (!execute_if_builtin(vtr, hashtable, node->left))
			execve(node->left->path, node->left->args, NULL);
		exit(0);
	}
	else
	{
		wait(&status);
		if ((ft_strncmp(node->cmds, "&&", 2) == 0 && WEXITSTATUS(status) == 0) 
			|| (ft_strncmp(node->cmds, "||", 2) == 0 && WEXITSTATUS(status) != 0))
			if (!execute_if_builtin(vtr, hashtable, node->right))
				execve(node->right->path, node->right->args, NULL);
	}
}


void	simple_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
		return ;
	}
	else if (pid == 0)
	{
		if (!execute_if_builtin(vtr, hashtable, node))
			execve(node->path, node->args, NULL);
		exit(0);
	}
	else
		wait(NULL);
}


// Pipe original e com heredoc

// if ((node->type == TYPE_OPERATOR && node->weight == OP_PIPE) || (node->type == TYPE_REDIRECT))
// 	{
// 		pipe(fd);
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
// 			return ;
// 		}
// 		if (pid == 0) // child
// 		{
// 			dup2(current_fd, STDIN_FILENO);
// 			close(fd[0]);
// 			if (!execute_if_builtin(vtr, hashtable, node->left) && node->left->type == TYPE_COMMAND)
// 				execve(node->left->path, node->left->args, NULL);
// 			// exit(0);
// 		}
// 		else // parent
// 		{
// 			wait(NULL);
// 			dup2(fd[0], STDIN_FILENO);
// 			close(fd[1]);
// 			if (current_fd != STDIN_FILENO)
// 				close(current_fd);
// 			// if (!execute_if_builtin(vtr, hashtable, node->right) && node->right->type == TYPE_COMMAND)
// 				// execve(node->right->path, node->right->args, NULL);
// 		}
// 	}



// Redirect original

// else if (node->type == TYPE_REDIRECT)
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			ft_fprintf(2, "minishell: fucker\n");
// 			return ;
// 		}
// 		else if (pid == 0)
// 		{
// 			if (!execute_if_builtin(vtr, hashtable, node->left))
// 				execve(node->left->path, node->left->args, NULL);
// 			exit(0);
// 		}
// 		else
// 			wait(NULL);
// 	}