#include "../include/builtins.h"
#include "../include/segments.h"
#include "../include/exec.h"
#include "../include/hash.h"

void    init_redirects(t_vector *vtr)
{
    vtr->redirect[0].name = "<";
    vtr->redirect[0].function = redirect_input;
    vtr->redirect[1].name = ">";
    vtr->redirect[1].function = redirect_output;
    vtr->redirect[2].name = ">>";
    vtr->redirect[2].function = redirect_append;
    vtr->redirect[3].name = "<<";
    vtr->redirect[3].func_here = handle_heredoc;
    vtr->redirect[4].name = NULL;
    vtr->redirect[4].function = NULL;
}

t_bool  is_redirect(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
{
    while (vtr->redirect->name)
    {
        if (ft_strcmp(vtr->redirect->name, node->cmds) == 0)
        {
            if (ft_strcmp(vtr->redirect->name, "<<") == 0)
                vtr->redirect->func_here(hashtable, node->delim);
            else
                vtr->redirect->function(node->args[0]);
            return (true);
        }
        vtr->redirect++;
    }
    return (false);
}
