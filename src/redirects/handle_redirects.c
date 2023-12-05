#include "../include/builtins.h"
#include "../include/segments.h"
#include "../include/exec.h"
#include "../include/hash.h"

void    init_redirects(t_vector *vtr)
{
    vtr->redirect[0].name = "<";
    vtr->redirect[1].name = ">";
    vtr->redirect[2].name = ">>";
    vtr->redirect[3].name = "<<";
    vtr->redirect[4].name = NULL;
    vtr->redirect[0].function = redirect_input;
    vtr->redirect[1].function = redirect_output;
    vtr->redirect[2].function = redirect_append;
    vtr->redirect[3].function = NULL;
    vtr->redirect[4].function = NULL;
    vtr->redirect[0].func_here = NULL;
    vtr->redirect[1].func_here = NULL;
    vtr->redirect[2].func_here = NULL;
    vtr->redirect[3].func_here = handle_heredoc;
    vtr->redirect[4].func_here = NULL;
}

void  handle_redirects(t_vector *vtr, t_hashtable *hashtable, t_ast *node, t_exec *exec)
{
    t_redirect *current;

    current = vtr->redirect;
    while (current->name)
    {
        if (ft_strcmp(current->name, node->cmds) == 0)
        {
            if (ft_strcmp(current->name, "<<") == 0)
                current->func_here(node , hashtable, node->delim);
            else
			{
                current->function(node, node->delim);
				if(node->left)
					execute_forked_command(vtr, hashtable, node->left);
				if (node->right)
					exec_multi_cmds(vtr, hashtable, node->right, exec);
				break ;
			}
        }
        current++;
    }
}
