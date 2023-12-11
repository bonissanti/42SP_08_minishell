#include "../../minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_hashtable *hashtable = create_hashtable();
    t_vector vtr;

    init_hash(hashtable, envp);
    init_cmd(&vtr);
    init_redirects(&vtr);


    t_ast *head = NULL;

    t_ast *node1 = create_node(TYPE_COMMAND, "ls", DEFAULT);
    insert_ast(&head, node1);
    
    t_ast *node2 = create_node(TYPE_OPERATOR, "|", OP_PIPE);
    insert_ast(&head, node2);

    t_ast *node3 = create_node(TYPE_COMMAND, "wc", DEFAULT);
    insert_ast(&head, node3);
    
    t_ast *node4 = create_node(TYPE_OPERATOR, "|", OP_PIPE);
    insert_ast(&head, node4);

    t_ast *node5 = create_node(TYPE_COMMAND, "wc", DEFAULT);
    insert_ast(&head, node5);

    analyzing_cmd(&vtr, hashtable, head);
    handle_cmd(&vtr, hashtable, head);
    delete_node(head);
    destroy_hashtable(hashtable);
}