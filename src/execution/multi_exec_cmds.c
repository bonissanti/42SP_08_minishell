#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"

void	exec_multi_cmds(t_hashtable *hashtable, t_ast *root)
{
	t_exec exec;

	init_structs(&exec, 0, sizeof(t_exec));
    handle_redirects(hashtable, root);
	handle_pipes(hashtable, root, &exec);
	wait_for_children(root);
}

static void    assign_and_exec_pids(t_hashtable *hashtable, t_ast *node)
{
    if (node == NULL)
        return ;

    if (node->type == TYPE_COMMAND)
    {
        node->pid = fork();
        if (node->pid == 0)
        {
            if (node->left && node->left->type == TYPE_REDIRECT)
                swap_fd(node->left->fd, STDIN_FILENO);

            if (node->right && node->right->type == TYPE_REDIRECT)
                swap_fd(node->right->fd, STDOUT_FILENO);

            execute_forked_command(hashtable, node->cmds, node->args);
            // exit(node->exit_status);
            exit(EXIT_SUCCESS);
        }
    }
    else if (node->type == TYPE_OPERATOR || node->type == TYPE_REDIRECT)
    {
        assign_and_exec_pids(hashtable, node->left);
        assign_and_exec_pids(hashtable, node->right);
    }
}

static void    wait_for_children(t_ast *root)
{
    int status;

    if (root == NULL)
        return ;

    if (root->type == TYPE_COMMAND)
    {
        waitpid(root->pid, &status, 0);
        if (WIFEXITED(status))
            root->exit_status = WEXITSTATUS(status);
    }
    else if (root->type == TYPE_OPERATOR || root->type == TYPE_REDIRECT)
    {
        wait_for_children(root->left);
        wait_for_children(root->right);
    }
}

static void    handle_pipes(t_hashtable *hashtable, t_ast *root, t_exec *exec)
{
    int pipefd[2];

    if (root == NULL)
        return ;

    if (root->type == TYPE_OPERATOR && root->weight == OP_PIPE)
    {
        pipe(pipefd);
        backup_fd(&exec->old_stdin, &exec->old_stdout);
        swap_fd(pipefd[1], STDOUT_FILENO);
        assign_and_exec_pids(hashtable, root->left);
        restore_fd(exec->old_stdin, exec->old_stdout);
        swap_fd(pipefd[0], STDIN_FILENO);
        assign_and_exec_pids(hashtable, root->right);
        restore_fd(exec->old_stdin, exec->old_stdout);
    }
    else 
    {
        handle_pipes(hashtable, root->left, exec);
        handle_pipes(hashtable, root->right, exec);
    }
}

static void execute_forked_command(t_hashtable *hashtable, char *cmd, char **args)
{
	char *path;
	int result;

	result = verify_cmd_permissions(cmd);
	if (ft_strchr(cmd, '/') != NULL && result == 0) // tratamento para caminho absoluto'
	{
		if (result == 126) // tacar isso numa função para printar erro de permissão
			ft_fprintf(2, "minishell: %s: command not found\n", cmd);
		else if (result == 127)
			ft_fprintf(2, "minishell: %s: %s\n", cmd, strerror(errno));
		return ;
	}
	else
	{
		path = search(hashtable, "PATH")->value;
		cmd = build_cmd_path(cmd, path);
	}
	execve(cmd, args, NULL);
	ft_fprintf(2, "minishell: %s: %s\n", cmd, strerror(errno));
	exit(EXIT_FAILURE);
}