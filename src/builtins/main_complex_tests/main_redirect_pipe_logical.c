int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_hashtable *hashtable = create_hashtable();
    t_vector vtr;

    init_hash(hashtable, envp);
    init_exec_vector(&vtr);

    t_ast *root = NULL;

    t_ast *node1 = create_node(TYPE_COMMAND, "cat", DEFAULT);
    insert_ast(&root, node1, &vtr.exec);

    t_ast *node2 = create_node(TYPE_REDIRECT, "< sucker_expected.txt", OP_REDIRECT);
    insert_ast(&root, node2, &vtr.exec);

    t_ast *node3 = create_node(TYPE_PIPE, "|", OP_PIPE);
    insert_ast(&root, node3, &vtr.exec);

    t_ast *node4 = create_node(TYPE_COMMAND, "sort", DEFAULT);
    insert_ast(&root, node4, &vtr.exec);

    t_ast *node5 = create_node(TYPE_PIPE, "|", OP_PIPE);
    insert_ast(&root, node5, &vtr.exec);

    t_ast *node6 = create_node(TYPE_COMMAND, "wc", DEFAULT);
    insert_ast(&root, node6, &vtr.exec);

    backup_fd(&vtr.exec.old_stdin, &vtr.exec.old_stdout);
    exec_multi_cmds(&vtr, hashtable, root);

    delete_node(root);
    destroy_hashtable(hashtable);
}