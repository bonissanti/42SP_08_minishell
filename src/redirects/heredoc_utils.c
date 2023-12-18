#include "../include/minishell.h"

t_ast    *find_heredoc(t_ast *root)
{
    if (root == NULL)
        return (NULL);

    while (root)
    {
        if (root->type == TYPE_HEREDOC)
            return (root);
        else if (root->right)
            root = root->right;
        else
            break ;
    }
    return (NULL);
}