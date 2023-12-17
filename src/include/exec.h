#ifndef EXEC_H
# define EXEC_H

# include "./minishell.h"

//############################### CHECKER ####################################//

void	init_exec_vector(t_exec *exec);
t_bool	is_builtin(t_ast *node);
int		execute_builtin(t_hashtable *hashtable, t_ast *node);
void	init_redirects(t_exec *exec);
void    handle_redirects(t_ast *node);

//############################# REDIRECTIONS #################################//

void	redirect_input(t_ast *node, char *filename);
void	redirect_output(t_ast *node, char *filename);
void	redirect_append(t_ast *node, char *filename);
void	redirect_fds(t_ast *node);
void	analyze_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node);
void	simple_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node);
void	simple_redirect_out(t_exec *exec, t_hashtable *hashtable, t_ast *node, int *prev_pipe);
void 	handle_heredoc(t_hashtable *hash, t_exec *exec, t_ast *node);
char	*check_expansion(t_hashtable *env, char **line, size_t *len);
t_bool	verify_file_permissions(const char *file);
int		verify_cmd_permissions(const char *cmd);


//############################# OPERATOR #####################################//

void	handle_pipes(t_hashtable *hash, t_exec *exec, t_ast *node,
			int *prev_pipe);
void	handle_other(t_exec *exec, t_hashtable *hash, t_ast *node,
		int *prev_pipe);
void	execute_pipes(t_hashtable *hashtable, t_exec *exec, t_ast *node,
			int *prev_pipe, int *next_pipe);
void	logical_pipe(t_exec *exec, t_hashtable *hash, t_ast *node,
			int *prev_pipe);
void	simple_logical(t_exec *exec, t_hashtable *hash, t_ast *node,
			int status);
void	pipe_from_redirect(t_hashtable *hash, t_exec *exec, t_ast *node,
			int *prev_pipe);

//############################# PREPARE_EXEC #################################//

void	backup_fd(int *old_stdin, int *old_stdout);
void	swap_fd(int new_fd, int system_fd);
void	restore_fd(int reset_stdin, int reset_stdout);
char	*build_cmd_path(t_ast *node, char *path);
void	handle_error(t_ast *node, int result);
void 	analyze_if_print(t_ast *node, int index);
t_bool	analyze_cmd(t_hashtable *hashtable, t_ast *node);
void	analyze_heredoc(t_exec *exec, t_ast *node, t_hashtable *hashtable);

//############################# EXECUTION ####################################//

int		exec_simple(t_hashtable *hash, t_ast *node);
int		exec_multi_cmds(t_exec *exec, t_hashtable *hashtable, t_ast *root);
int		forking(t_ast *node);
int		exec_forked_cmd(t_hashtable *hashtable, t_ast *node);
void	close_all_fds(int *fd);
void    wait_for_children(t_ast *node);
// void	handle_cmd(t_exec *exec, t_hashtable *hashtable, t_ast *node); //temp

// void print_pipe_contents(int *pipefd); // Remover depois

void	ft_printf_fd(int fd);

#endif