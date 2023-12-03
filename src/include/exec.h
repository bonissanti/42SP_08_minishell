# include "../include/hash.h"
# include "../include/builtins.h"
# include "../include/ast.h"
# include <sys/wait.h>


typedef struct s_cmd
{
	char	*name;
	char	*cmd;
	void	(*function)(t_hashtable *hash_table, char **args);
}		t_cmd;

typedef struct s_redirect
{
	char	*name;
	void	(*func_here)(t_ast *node, t_hashtable *env, char *delim);
	void	(*function)(t_ast *node, char *filename);
}		t_redirect;

typedef struct s_vector
{
	t_redirect  redirect[5];
    t_cmd	    builtins[2];
}		t_vector;


//############################### VECTOR #####################################//

void	    init_cmd(t_vector *vtr);
t_bool		execute_if_builtin(t_vector *vtr, t_hashtable *hashtable, t_ast *node);
void        init_redirects(t_vector *vtr);
void        handle_redirects(t_vector *vtr, t_hashtable *hashtable, t_ast *node);

//############################# REDIRECTIONS #################################//

void	redirect_input(t_ast *node, char *filename);
void	redirect_output(t_ast *node, char *filename);
void	redirect_append(t_ast *node, char *filename);
void	handle_heredoc(t_ast *node, t_hashtable *env, char *delim);
char    *check_expansion(t_hashtable *env, char **line, size_t *len);
t_bool	verify_file_permissions(const char *file);
int 	verify_cmd_permissions(const char *cmd);

//############################# PREPARE_EXEC #################################//

void	backup_fd(int *old_stdin, int *old_stdout);
void	swap_fd(int new_fd, int system_fd);
void	restore_fd(int reset_stdin, int reset_stdout);
char    *build_cmd_path(t_ast *node , char *path);

//############################# EXECUTION ####################################//

void	exec_multi_cmds(t_vector *vtr, t_hashtable *hashtable, t_ast *root);
void    close_all_fds(int *fd);
// void	handle_cmd(t_vector *vtr, t_hashtable *hashtable, t_ast *node); //temp

// void print_pipe_contents(int *pipefd); // Remover depois

void ft_printf_fd(int fd);