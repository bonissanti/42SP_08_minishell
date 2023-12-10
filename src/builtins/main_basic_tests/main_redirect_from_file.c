#include "../include/hash.h"
#include "../include/builtins.h"
#include "../include/segments.h"
#include "../include/ast.h"
#include "../include/exec.h"

void	print_ast(t_ast *node)
{
	if (node)
	{
		size_t i = -1;

		printf("node->cmds: %s\n", node->cmds);
		while (node->args[++i])
			printf("node->args[%zu]: %s\n", i, node->args[i]);
		printf("node->path: %s\n", node->path);
		printf("node->in_fd: %d\n", node->in_fd);
		printf("node->out_fd: %d\n", node->out_fd);
		printf("node->delim: %s\n", node->delim);
		printf("node->weight: %d\n", node->weight);
		printf("node->type: %d\n", node->type);
		// print_ast(node->left);
		// print_ast(node->right);
	}
}

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

	t_ast *node1 = create_node(TYPE_COMMAND, "cat", DEFAULT);
	insert_ast(&head, node1);
	
	t_ast *node4 = create_node(TYPE_REDIRECT, "<", OP_REDIRECT);
	insert_ast(&head, node4);

	t_ast *node7 = create_node(TYPE_FILE, "sucker.txt", DEFAULT);
	insert_ast(&head, node7);

	analyzing_cmd(&vtr, hashtable, head);
	handle_cmd(&vtr, hashtable, head);
	delete_node(head);
	destroy_hashtable(hashtable);
}


// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	while (1)
// 	{
// 		ft_putstr_fd("~$ ", 1);
// 		char *input = get_next_line(0);
// 		char *trimmed_input = ft_strtrim(input, "\n");
// 		free(input);

// 		if (ft_strcmp(trimmed_input, "exit") == 0)
// 		{
// 			free(trimmed_input);
// 			exit(0);
// 		}
// 		else if (ft_strcmp(trimmed_input, "/nfs/homes/brunrodr/09.MINISHELL/V_atual/42SP_08_minishell/src/execution/*.c") == 0)
// 		{
// 			handle_wildcard(trimmed_input);
// 			free(trimmed_input);
// 		}
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char **num_args;
	
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	t_hashtable *hash_table = create_hashtable();	
	
// 	init_hash(hash_table, envp);
// 	char *input;
// 	char *trimmed_input;

// 	while (1)
// 	{
// 		ft_putstr_fd("~$ ", 1);
// 		input = get_next_line(0);

// 		trimmed_input = ft_strtrim(input, "\n");
// 		free(input);

// 		num_args = ft_split(trimmed_input, ' ');
// 		free(trimmed_input);
		
		// if (ft_strcmp(num_args[0], "export") == 0)
        //    ft_export(hash_table, num_args);

		// if (ft_strcmp(num_args[0], "echo") == 0)
		// 	analyzing_quotes(hash_table, num_args + 1);
       
		// if (ft_strcmp(num_args[0], "exit") == 0)
		// 	ft_exit(hash_table, num_args);

		// if (ft_strcmp(num_args[0], "unset") == 0)
		// 	ft_unset(hash_table, num_args);
		
		// if (ft_strcmp(num_args[0], "env") == 0)
		// 	ft_env(hash_table, num_args);

		// if (ft_strcmp(num_args[0], "cd") == 0)
		// 	ft_cd(hash_table, num_args);

		// if (ft_strcmp(num_args[0], "pwd") == 0)
		// 	ft_pwd(hash_table, num_args);

		// if (ft_strcmp(num_args[0], "<<") == 0)
		// 	handle_heredoc(hash_table, num_args[1]);

		// if (ft_strcmp(argv[1], "*.c") == 0)
		// 	handle_wildcard(argv[1]);

		// if (ft_strcmp(num_args[0], "expand") == 0)
		// 	expand_tilde(hash_table, num_args[1]);

		// safe_free((void **)&num_args);

// 	}
// 	destroy_hashtable(hash_table);
// 	free(input);
// 	free(hash_table);
// 	return (0);
// }
