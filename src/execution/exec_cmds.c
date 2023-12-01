#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"
#include <sys/wait.h>

void	simple_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node);
void	execute_and_or(t_vector  *vtr, t_hashtable *hashtable, t_ast *node);
static void	complet_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node);

void	handle_cmd(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	if (node == NULL)
		return ;

	if ((node->type == TYPE_OPERATOR && ft_strcmp(node->cmds, "|") == 0 )) //pipes
		complet_execution(vtr, hashtable, node);

	else if (node->type == TYPE_OPERATOR && ft_strcmp(node->cmds, "|" ) != 0)
		execute_and_or(vtr, hashtable, node);

	else if (node->type == TYPE_REDIRECT)
		simple_execution(vtr, hashtable, node->left);

	else if (node->type == TYPE_COMMAND && node->left == NULL && node->right == NULL)
		simple_execution(vtr, hashtable, node);

	// if (node->right && ft_strcmp(node->cmds, "&&") != 0) 
	// 	handle_cmd(vtr, hashtable, node->right);
}

t_ast *branch_tip(t_ast *node)
{
	t_ast *first;

	if(!node)
		return (NULL);
	first = node;
	if(first->left == NULL)
		return (first);
	else
	{
		while(first->left)
			first = first->left;
	}
	return(first);
}

void	set_fds(int (*fd)[2])
{
	int	i;

	i = 0;
	while (i <= 100)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("fd");
			return ;
		}
		i++;
	}
}

void	close_unused_fds(int (*fds)[2], int pid, int total_fds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= total_fds)
	{
		if (fds[i][j] != fds[pid - 1][j])
			close(fds[i][j]);
		i++;
	}
	i = 0;
	j = 1;
	while (i <= total_fds)
	{
		if (fds[i][j] != fds[pid][j])
			close(fds[i][j]);
		i++;
	}
}

void	close_all_fds(int (*fds)[2], int total_fds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= total_fds)
	{
		close(fds[i][j]);
		close(fds[i][j + 1]);
		i++;
	}
}

int total_branchs(t_ast *node)
{
	int total;

	total = 0;
	if(!node)
		return(total);
	while(node)
	{
		total++;
		node = node->right;
	}
	return(total);
	ft_printf("Total: %d\n", total);
}

// static void child_executor(t_vector *vtr, t_hashtable *hashtable, t_ast *node, int *fd, int i)
// {

// }

// static void parent_executor(t_vector *vtr, t_hashtable *hashtable, t_ast *node, int *fd)
// {
// 	// (void)vtr;
// 	// (void)hashtable;
// 	// (void)node;
// 	// (void)fd;
// 	dup2(fd[0], STDIN_FILENO);
//    	close(fd[0]);
//    	close(fd[1]);

// 	// close(fd[i][1]);
// 	// if (node->in_fd != STDIN_FILENO)
// 	// 	close(node->in_fd);
// 	// dup2(fd[i][0], STDIN_FILENO);
// 	// if (node->type == TYPE_REDIRECT)
// 	// 	simple_execution(vtr, hashtable, branch_tip(node->right));
// 	// dup2(fd[i - 1][0], STDIN_FILENO);
// 	// close(fd[i - 1][0]);
// 	// // dup2(fd[i][1], STDOUT_FILENO);
// 	// // close(fd[i][1]);
// 	// if(!node->right)
// 	// 	return ;
// 	if (!execute_if_builtin(vtr, hashtable, branch_tip(node->right))																						
// 		&& branch_tip(node->right)->type != TYPE_REDIRECT)
// 		exit(execve(branch_tip(node->right)->path, branch_tip(node->right)->args, NULL));
// }

static void	complet_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	int fd[100][2];
	int pid[100][1];
	pid_t pid;
	int status;
	int exit_status;
	int i = 0;
	int total_pipes = total_branchs(node);
	int out_bkp = dup(STDOUT_FILENO);

	// pipe(fd);
	set_fds(fd);
	while(i < total_pipes)
	{
		pid[i][0] = fork();
		if (pid[i][0] == 0)
		//here
		i++;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
		return ;
	}

	node = node->right;
	i++;
	waitpid(pid, &status, 0);
	if(WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
}

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
		if (!execute_if_builtin(vtr, hashtable, branch_tip(node->left)))
			exit(execve(branch_tip(node->left)->path, branch_tip(node->left)->args, NULL));
	}
	else
	{
		wait(&status);
		if ((ft_strncmp(node->cmds, "&&", 2) == 0 && WEXITSTATUS(status) == 0)
			|| (ft_strncmp(node->cmds, "||", 2) == 0 && WEXITSTATUS(status) != 0))
			if (!execute_if_builtin(vtr, hashtable, branch_tip(node->right)))
				exit(execve(branch_tip(node->right)->path, branch_tip(node->right)->args, NULL));
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
			exit(execve(node->path, node->args, NULL));
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
// 			dup2(current_in_fd, STDIN_FILENO);
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