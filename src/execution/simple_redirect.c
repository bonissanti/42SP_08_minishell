#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/segments.h"

static void	redirect_fds(t_ast *node, int *prev_pipe)
{
	if (node->in_fd != -1)
	{
		dup2(node->in_fd, STDIN_FILENO);
		close(node->in_fd);
	}
	if (node->out_fd != -1)
	{
		dup2(node->out_fd, STDOUT_FILENO);
		close(node->out_fd);
	}
}


void	simple_redirect(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
    int next_pipe[2];

    if (node == NULL)
        return ;
    node->pid = fork();
    if (node->pid == 0)
    {
        pipe(next_pipe);
        dup2(next_pipe[0], STDIN_FILENO);
        close(next_pipe[0]);
        close(next_pipe[1]);
        handle_pipes(hashtable, vtr, node->right->right, next_pipe);
    }
    else
    {
        if (node->type == TYPE_REDIRECT)
        {
            redirect_fds(node, NULL);
		    execute_command(vtr, hashtable, node->left);
        }
    }
}