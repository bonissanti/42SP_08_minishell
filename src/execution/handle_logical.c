#include "../../minishell.h"

void    logical_pipe(t_vector *vtr, t_hashtable *hash, t_ast *node, int *prev_pipe)
{
    pid_t pid;

    if (node == NULL)
        return ;

    if (node->type == TYPE_LOGICAL && node->weight == OP_LOGICAL)
    {
        pid = fork();
        if (*prev_pipe != -1)
        {
            dup2(prev_pipe[0], STDIN_FILENO);
            close(prev_pipe[0]);
        }
        if (pid == 0)
        {
            execute_forked_command(hash, node->left);
            exit(node->left->exit_status);
        }
        else
        {
            waitpid(pid, &node->left->exit_status, 0);
            if (node->left->exit_status == 0 && !ft_strncmp(node->cmds, "&&", 2))
                exec_multi_cmds(vtr, hash, node->right);
            else if (node->left->exit_status != 0 && !ft_strncmp(node->cmds, "||", 2))
                exec_multi_cmds(vtr, hash, node->right);
        }
    }
}

void    simple_logical(t_vector *vtr, t_hashtable *hash, t_ast *node, int status)
{
    if (status == 0 && !ft_strncmp(node->cmds, "&&", 2))
        exec_multi_cmds(vtr, hash, node->right);
    else if (status != 0 && !ft_strncmp(node->cmds, "||", 2))
        exec_multi_cmds(vtr, hash, node->right);
}