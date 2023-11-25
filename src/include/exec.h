# include "../include/hash.h"
# include "../include/builtins.h"
# include "../include/ast.h"

typedef struct s_cmd
{
	char	*name;
	char	*cmd;
	void	(*function)(t_hashtable *hash_table, char **args);
}		t_cmd;

typedef struct s_redirect
{
	char	*name;
	void	(*function)(char *filename);
	void	(*func_here)(t_hashtable *env, char *delim);
}		t_redirect;

typedef struct s_vector
{
	t_redirect	*redirect;
    t_cmd	    *builtins;
}		t_vector;


//############################### VECTOR #####################################//

void		init_builtins(t_cmd *cmd);
t_bool		is_builtins(t_cmd *builtins, t_hashtable *hashtable, t_ast *node);
void		execute_builtins(t_cmd *builtins, t_hashtable *hashtable, t_ast *node);
void        init_redirects(t_vector *vtr);
t_bool      is_redirect(t_vector *vtr, t_hashtable *hashtable, t_ast *node);

//############################# REDIRECTIONS #################################//

void	redirect_input(char *filename);
void	redirect_output(char *filename);
void	redirect_append(char *filename);
void	handle_heredoc(t_hashtable *env, char *delim);
char    *check_expansion(t_hashtable *env, char **line, size_t *len);
t_bool	verify_file_permissions(const char *file);
int 	verify_cmd_permissions(const char *cmd);

//############################# PREPARE_EXEC #################################//

void	analyzing_cmd(t_hashtable *hashtable, t_ast *node);
char    *build_cmd_path(t_ast *node , char *path);
