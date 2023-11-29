#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"

// static void	complet_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
// {
// 	int fd[2];
// 	pid_t pid;
// 	t_ast *first_left_branch = branch_tip(node->left);
// 	t_ast *first_right_branch = branch_tip(node->right);

// 	pipe(fd);
// 	pid = fork();
// 	int current_fd = node->in_fd;
// 	if (pid == -1)
// 	{
// 		ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
// 		return ;
// 	}
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		// if (node->in_fd != STDIN_FILENO)
// 		// {
// 		// 	dup2(node->in_fd, STDIN_FILENO);
// 		// 	close(node->in_fd);
// 		// }
// 		// if (node->out_fd != STDOUT_FILENO)
// 		// {
// 		// 	dup2(node->out_fd, STDOUT_FILENO);
// 		// 	close(node->out_fd);
// 		// }
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		if (node->type == TYPE_REDIRECT)
// 			simple_execution(vtr, hashtable, node->left->left);
// 		if (!execute_if_builtin(vtr, hashtable, node->left))
// 			execve(first_left_branch->path, first_left_branch->args, NULL);
// 			// execve(node->left->path, node->left->args, NULL);
// 		exit(0);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		close(fd[1]);
// 		if (node->in_fd != STDIN_FILENO)
// 			close(node->in_fd);
// 		dup2(fd[0], STDIN_FILENO);
// 		print_pipe_contents(fd);
// 		if (node->type == TYPE_REDIRECT)
// 			simple_execution(vtr, hashtable, node->right->left);
// 		if (!execute_if_builtin(vtr, hashtable, node->right) && node->right->type != TYPE_REDIRECT)
// 			execve(first_right_branch->path, first_right_branch->args, NULL);
// 			// execve(node->right->path, node->right->args, NULL);
// 	}
// }
