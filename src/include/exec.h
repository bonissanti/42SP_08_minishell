# include "../include/hash.h"
# include "../include/builtins.h"
# include "../include/ast.h"
# include <sys/wait.h>

struct s_exec;

typedef struct s_cmd
{
	char	*name;
	char	*cmd;
	void	(*function)(t_hashtable *hash_table, char **args);
}		t_cmd;

typedef struct s_redirect
{
	char	*name;
	void	(*function)(t_ast *node, char *filename);
}		t_redirect;

typedef struct s_vector
{
	t_exec		exec;
	t_redirect  redirect[5];
    t_cmd	    builtins[2];
}		t_vector;


//############################### VECTOR #####################################//

void	    init_cmd(t_vector *vtr);
void		init_exec_vector(t_vector *vtr);
t_bool		execute_if_builtin(t_vector *vtr, t_hashtable *hashtable, t_ast *node);
void        init_redirects(t_vector *vtr);
void		handle_redirects(t_vector *vtr, t_ast *node);

//############################# REDIRECTIONS #################################//

void	redirect_input(t_ast *node, char *filename);
void	redirect_output(t_ast *node, char *filename);
void	redirect_append(t_ast *node, char *filename);
void	analyze_redirect(t_vector *vtr, t_hashtable *hashtable, t_ast *node);
void    simple_redirect_out(t_vector *vtr, t_hashtable *hashtable, t_ast *node, int *prev_pipe);
void	handle_heredoc(t_vector *vtr, t_ast *node, t_hashtable *env, char *delim);
char    *check_expansion(t_hashtable *env, char **line, size_t *len);
t_bool	verify_file_permissions(const char *file);
int 	verify_cmd_permissions(const char *cmd);

//############################# OPERATOR #####################################//

void 	handle_pipes(t_hashtable *hash, t_vector *vtr, t_ast *node, int *prev_pipe);
void	execute_pipes(t_hashtable *hashtable, t_vector *vtr, t_ast *node, int *prev_pipe, int *next_pipe);
void    logical_pipe(t_vector *vtr, t_hashtable *hash, t_ast *node, int *prev_pipe);
void    simple_logical(t_vector *vtr, t_hashtable *hash, t_ast *node, int status);
void    pipe_from_redirect(t_hashtable *hash, t_vector *vtr, t_ast *node, int *prev_pipe);

//############################# PREPARE_EXEC #################################//

void	backup_fd(int *old_stdin, int *old_stdout);
void	swap_fd(int new_fd, int system_fd);
void	restore_fd(int reset_stdin, int reset_stdout);
char    *build_cmd_path(t_ast *node , char *path);
void	handle_error(t_ast *node, int result);

//############################# EXECUTION ####################################//

void	simple_redirect_in(t_vector *vtr, t_hashtable *hashtable, t_ast *node);
void	exec_multi_cmds(t_vector *vtr, t_hashtable *hashtable, t_ast *root);
void 	execute_command(t_vector *vtr, t_hashtable *hashtable, t_ast *node);
void    close_all_fds(int *fd);
// void	handle_cmd(t_vector *vtr, t_hashtable *hashtable, t_ast *node); //temp

// void print_pipe_contents(int *pipefd); // Remover depois

void ft_printf_fd(int fd);