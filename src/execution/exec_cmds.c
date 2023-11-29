#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"

static void	simple_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node, int input_fd);
// void	execute_and_or(t_vector  *vtr, t_hashtable *hashtable, t_ast *node);
static void	complet_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node);
void	child_process(t_vector *vtr, t_hashtable *hashtable, t_ast *node, int input_fd, int *fd);
void	parent_process(int *input_fd, int *fd);

void	handle_cmd(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
	if (node == NULL)
		return ;

	if ((node->type == TYPE_OPERATOR && ft_strcmp(node->cmds, "|") == 0 )) //pipes
		complet_execution(vtr, hashtable, node);

	// else if (node->type == TYPE_OPERATOR && ft_strcmp(node->cmds, "|" ) != 0)
	// 	execute_and_or(vtr, hashtable, node);

	// else if (node->type == TYPE_REDIRECT)
	// 	simple_execution(vtr, hashtable, node->left

	// else if (node->type == TYPE_COMMAND && node->left == NULL && node->right == NULL)
	// 	simple_execution(vtr, hashtable, node);

	if (node->right && ft_strcmp(node->cmds, "&&") != 0) 
		handle_cmd(vtr, hashtable, node->right);
}



t_ast *branch_tip(t_ast *node)
{
	t_ast *first;

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



static void	complet_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
    int fd[2];
    pid_t pid;
    int input_fd = STDIN_FILENO;

    while (node->type == TYPE_OPERATOR)
    {
        pipe(fd);
        pid = fork();
        if (pid == -1)
        {
            ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
            return ;
        }
        if (pid == 0)
            child_process(vtr, hashtable, node->left, input_fd, fd);
        else
			parent_process(&input_fd, fd);
		node = node->right;
    }
    if (node != NULL && node->type == TYPE_COMMAND)
        simple_execution(vtr, hashtable, node, input_fd);
}


void	child_process(t_vector *vtr, t_hashtable *hashtable, t_ast *node, int input_fd, int *fd)
{
    close(fd[0]);
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (node->right)
		dup2(fd[1], STDOUT_FILENO);
	if (!execute_if_builtin(vtr, hashtable, node))
		execve(node->path, node->args, NULL);
	exit(0);
}


void	parent_process(int *input_fd, int *fd)
{
	wait(NULL);
	close(fd[1]);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	*input_fd = fd[0];
	// node = &(*node)->right;
}






static void	simple_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node, int input_fd)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
		return ;
	}
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
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