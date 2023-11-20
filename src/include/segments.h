#ifndef SEGMENTS_H
# define SEGMENTS_H

# include "hash.h"
# include <dirent.h>
# include <stdlib.h>
# include <sys/stat.h>

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
	t_bool				space_dollar;
}						t_quote_state;

typedef struct s_dollar
{
	t_bool				has_dollar;
}						t_expand;

typedef struct s_lex
{
	char				*ptr;
	char				*segment;
	int					type;
	int					prev_type;
	t_hashtable			*env;
	t_quote_state		state;
	t_expand			dollar;
}						t_lex;

//############################### LIST ###################################

t_segment				*new_segments(char *str);
void					add_segments(t_segment **head, char *str);
char					*join_segments(t_segment *head);
void					free_segments(t_segment *head);

//############################### QUOTES ###################################

t_lex					*init_lex(t_hashtable *env, char *arg);
t_quote_state			init_quote_state(void);
size_t					even_close_quotes(char *str);
void					is_quotes(t_hashtable *env, char **args);
void					final_process(t_lex *quote, t_segment **head,
							char **args, size_t *len);

//############################### DOLLAR ###################################

void					expand_variable(t_lex *quote, t_segment **head,
							size_t *len);
t_expand				init_expand_dollar(void);

//############################### TILDE ###################################

char					*expand_tilde(t_hashtable *hashtable, char *str);

//############################### UTILS ###################################

void					error_close_quotes(t_lex *quote);
t_bool					check_dollar_space(char *str);
t_bool					check_handle_error(t_lex *quote, char **args, int i);
char					*ft_strndup(const char *str, size_t num);
size_t					custom_strcspn(const char *str, char *delim1);
t_bool					is_whitespace(char c);

//############################### WILDCARD ###################################

void					init_structs(void *structs, size_t struct_size);
void					handle_wildcard(char *pattern);
char					*ft_strtok(char *str, const char *delim);
void 					finish_wildcard(t_segment *head, t_file *file);

#endif