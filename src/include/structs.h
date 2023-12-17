#ifndef STRUCTS_H
# define STRUCTS_H

#include "../../libft/libft.h"
#include <dirent.h>

//############################### Parser ###################################

typedef enum
{
    TYPE_COMMAND,
    TYPE_LOGICAL,
    TYPE_SUBSHELL,
    TYPE_PIPE,
	TYPE_FILE,
	TYPE_HEREDOC,
    TYPE_REDIRECT,
}    t_type;

typedef enum
{
	OP_REDIRECT = 3,
	OP_HEREDOC = 3,
	OP_PIPE = 3,  
	OP_LOGICAL = 3,
	DEFAULT = 0,
}	t_op;

typedef enum 
{
	IDENTIFIER,
	INFILE,
	REDIRECT,
	HERE_DOC,
	APPEND,
	PIPE,
	O_PARENTESIS,
	C_PARENTESIS,
	AND,
	OR,
	EXPAND,
	WILD
} t_tkn_type;

typedef struct s_tkn_list 
{
	t_tkn_type			type;
	char				*content;
	struct s_tkn_list	*next;
	struct s_tkn_list	*prev;
} t_tkn_list;

typedef struct s_cmd_list
{    
    t_type 	type;
    char *args;
    t_op	weight;
    char *infile;
    char *outfile;
	int	here_doc_fd;
	t_bool here_doc;
	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;
} t_cmd_list;

//############################### Ast ###################################

typedef struct s_ast
{
	
	char *cmds;
	char **args;
	char *path;
	char *delim;
	char *test;
	char *infile;
	char *outfile;
	int num_status;
	int	in_fd;
	int	out_fd;
	t_op weight;
	t_type type;
	pid_t pid;
	t_bool print_hdoc;
	t_bool print_redir;
	// t_bool is_freed; transferir pra t_cmd_list
	t_bool subshell;
	struct s_ast *left;
	struct s_ast *right;
} 	t_ast;

typedef struct s_exec
{
	int prev[2];
	int next[2];
	int	in_fd;
	int	out_fd;
	int old_stdin;
	int old_stdout;
	int count_hdoc;
	int count_pipes;
	int count_redir;
}	t_exec;

//############################### Hash ###################################

typedef struct s_hash
{
	char *key;
	char *value;
	struct s_hash *next;
}			t_hash;	

typedef struct s_hashtable
{
	int num_keys;
	t_hash *buckets[101];
	t_hash *home;
}			t_hashtable;

//############################### Exec ###################################

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
    t_cmd	    builtins[7];
}		t_vector;

//############################### Builtins ###################################

typedef struct s_env
{
	char	*key;
	char	**env;
	char	*value;
	char	**equals_sign;
	int		num_env;
}			t_env;

//############################### Segments ###################################

typedef struct s_segments
{
	char				*str;
	struct s_segments	*next;
}						t_segment;

/**
 * Data structure: t_files
 * -----------------
 * Is a linked list used to store the files that are found by the wildcard
 * expansion. Basically in file have the name of the file and the next pointer
 * points to the next file. In function 'handle_wildcard' the files are added
 * to the linked list and checked if files and patterns match.
 * 
 * @param: *file: The name of the file.
 * @param: *next: The pointer to the next file.
 * 
 */

typedef struct s_file
{
	char				*token;
	char				*directory;
	DIR					*dir;
	struct dirent		*entry;
	struct stat			entry_stat;
}						t_file;

typedef struct s_quote_state
{
	t_bool				single_open;
	t_bool				double_open;
	t_bool				escape_next;
	t_bool				space_dollar;
}						t_quote_bool;

typedef struct s_dollar
{
	t_bool				has_dollar;
}						t_expand;

typedef struct s_lex
{
	char				*ptr;
	char				*segment;
	t_hashtable			*env;
	t_quote_bool		state;
	t_expand			dollar;
}						t_lex;

//############################### Global ###################################

typedef struct s_global{
	char		*readline_input;
	t_tkn_list	*tkn_list;
	t_cmd_list	*cmd_list;
	int			exit_status;
	int			cmd_status;
	t_hashtable *hash;
	t_ast		*ast;

} t_global;

#endif
