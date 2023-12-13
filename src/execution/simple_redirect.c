#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/segments.h"

static void	redirect_fds(t_ast *node, int *prev_pipe)
{
	if (prev_pipe != NULL)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
	}
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

void	simple_redirect_in(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
    int next_pipe[2];

    if (node == NULL)
        return ;
    if (node->type == TYPE_REDIRECT)
    {
        node->pid = fork();
        if (node->pid == 0 && node->right != NULL && node->right->type == TYPE_PIPE)
        {
            pipe(next_pipe);
            dup2(next_pipe[0], STDIN_FILENO);
            close(next_pipe[0]);
            close(next_pipe[1]);
            handle_pipes(hashtable, vtr, node->right->right, next_pipe);
        }
        else
        {
            if (node->type == TYPE_REDIRECT && node->print_redir == true)
            {
                redirect_fds(node, NULL);
	    	    execute_command(vtr, hashtable, node->left);
            }
        }
        }
    else if (node->right != NULL && node->right->type == TYPE_REDIRECT)
        exec_multi_cmds(vtr, hashtable, node->right);
}






void	simple_redirect_out(t_vector *vtr, t_hashtable *hashtable, t_ast *node,
		int *prev_pipe)
{
	int	next_pipe[2];

	if (vtr->exec.count_pipes >= 1)
		pipe(next_pipe);
	if (node->type == TYPE_REDIRECT)
	{
		node->pid = fork();
		redirect_fds(node, prev_pipe);
		if (node->pid == 0)
		{
			if (node->type == TYPE_REDIRECT && node->print_redir == true)
			{
				if (node->in_fd != -1 && vtr->exec.count_pipes >= 1)
				{
					dup2(next_pipe[1], STDOUT_FILENO);
					close(next_pipe[1]);
				}
				execute_command(vtr, hashtable, node->left);			
				exit(0);
			}
		}
		else
		{
			restore_fd(vtr->exec.old_stdin, vtr->exec.old_stdout);
			// if (vtr->exec.count_pipes >= 1 && node->in_fd != 0)
			// 	close(prev_pipe[1]);
			check_pipe(vtr, hashtable, node, next_pipe);
		}
	}
	if (node->right != NULL && node->right->type == TYPE_REDIRECT)
		exec_multi_cmds(vtr, hashtable, node->right);
	else if (node->right && node->type == TYPE_REDIRECT && node->right->type == TYPE_LOGICAL)
	{
		waitpid(node->pid, &node->left->num_status, 0);
		simple_logical(vtr, hashtable, node->right, node->left->num_status);
	}
}