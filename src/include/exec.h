# include "../include/hash.h"
# include "../include/builtins.h"
# include "../include/ast.h"


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
