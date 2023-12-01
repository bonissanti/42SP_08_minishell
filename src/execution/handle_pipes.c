#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"

// static void	handle_pipes(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
// {
//     int fd[2];
//     pid_t pid;
//    	t_exec rdir;

//     // rdir.in_fd = STDIN_FILENO;
// 	// rdir.out_fd = STDOUT_FILENO;
// 	rdir.current_pipe = STDIN_FILENO;
// 	rdir.is_last_cmd = false;
//     while (node)
//     {
// 		if (node->type == TYPE_REDIRECT)
// 			simple_execution(vtr, hashtable, node->left);

//         pipe(fd);
//         pid = fork();
//         if (pid == -1)
//         {
//             ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
//             return ;
//         }
//         if (pid == 0)
// 		{
// 			// ft_fprintf(2, "Pai: vai filhão\n");
// 			if (node->right == NULL)
// 				rdir.is_last_cmd = true;

// 			if (node->type == TYPE_OPERATOR)
// 			{
// 				// ft_fprintf(2, "Filho: entrei no exec_cmd_in_pipe\n");
// 				exec_cmds_in_pipe(vtr, hashtable, node, rdir, fd);
// 			}
//         	else
// 			{
// 				// ft_fprintf(2, "Pai: entrei aqui no simple\n");
// 				// ft_fprintf(2, "node is %s\n", node->cmds);
// 				if (node->type == TYPE_REDIRECT)
// 					simple_execution(vtr, hashtable, node->left);
// 				else
// 					simple_execution(vtr, hashtable, node);
// 			}
// 			exit(0);
// 		}
//         else
// 			parent_process(rdir, fd);
// 		if (node->type == TYPE_OPERATOR)
// 			node = node->right;
// 		else
// 			node = NULL;
//     }
// }


// void exec_cmds_in_pipe(t_vector *vtr, t_hashtable *hashtable, t_ast *node, t_exec rdir, int *fd)
// {
//     close(fd[0]);
// 	// ft_printf("Filho: rdir.current_pipe: %d\n", rdir.current_pipe);
//     if (rdir.is_last_cmd)
// 		dup2(node->out_fd, STDOUT_FILENO);
//     else
// 	{
//         dup2(fd[1], STDOUT_FILENO);
// 		// ft_fprintf(2, "Filho :entrei aqui no fd[1]\n");
// 	}
// 	ft_fprintf(2, "fd[1]: %d\n", fd[1]);
//     if (!execute_if_builtin(vtr, hashtable, node->left) && node->left->type == TYPE_COMMAND)
// 	{
// 		ft_fprintf(2, "Filho: Executando cmd shell: %s\n", node->left->path);
//         execve(node->left->path, node->left->args, NULL);
// 	}
//     exit(0);
// }


// void	parent_process(t_exec rdir, int *fd)
// {
// 	wait(NULL);
// 	close(fd[1]);
// 	if (rdir.current_pipe != STDIN_FILENO)
// 	{
// 		ft_fprintf(2, "Pai: Fechando o current_pipe %d\n", rdir.current_pipe);
// 		close(rdir.current_pipe);
// 	}
// 	rdir.current_pipe = fd[0];
// 	// ft_fprintf(2, "Pai: Atualizando current_pipe: %d\n", rdir.current_pipe);
// }


// static void	simple_execution(t_vector *vtr, t_hashtable *hashtable, t_ast *node)
// {
// 	pid_t pid;

// 	ft_fprintf(2, "Filho: O comando é %s\n", node->cmds);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
// 		return ;
// 	}
// 	else if (pid == 0)
// 	{
// 		ft_fprintf(2, "Filho: Executando no simple\n");

// 		if (!execute_if_builtin(vtr, hashtable, node))
// 		{
// 			ft_fprintf(2, "Filho: Executando cmd shell: %s\n", node->path);
// 			execve(node->path, node->args, NULL);
// 		}
// 		exit(0);
// 	}
// 	else
// 		wait(NULL);
// }