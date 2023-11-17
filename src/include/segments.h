#ifndef SEGMENTS_H
# define SEGMENTS_H

// #include <string>
# include "hash.h"
# include <stdlib.h>

/**
 * Data structure: t_segment
 * -----------------
 * Is used to store the segments of the command line. Understood segments
 * as the parts of the command line that are separated by quotes, dollar signs
 * and wildcards. 
 * 
 * @param: *str: The string that contains the segment.
 * @param: *next: The pointer to the next segment.
 * 
 */

typedef struct s_segments
{
	char				*str;
	struct s_segments	*next;
}						t_segment;

/**
 * Struct: t_quote_state
 * -----------------
 * Is used as a flag to keep track of the state of the quotes, this is
 * important because the function 'is_quotes' have at least 4 different
 * behaviors depending on the state of the quotes.
 * 
 * @param: single_open: Flag to keep track of the state of the single quotes.
 * @param: double_open: Flag to keep track of the state of the double quotes.
 * @param: space_dollar: Flag to keep track of the state of the dollar sign.
 * 
 */


typedef struct s_quote_state
{
	t_bool				single_open;
	t_bool				double_open;
	t_bool				space_dollar;
}						t_quote_state;

/**
 * Struct: t_dollar
 * -----------------
 * Is used as a flag by 'ft_export' to check if the argument contains a dollar.
 * 
 * @param: has_dollar: Flag to keep track of the state of the dollar sign.
 * 
 */

typedef struct s_dollar
{
	t_bool				has_dollar;
}						t_expand;

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

typedef struct s_files
{
	char				*file;
	char				*content;
	struct s_files		*next;
}					t_files;

/**
 * Struct: t_lex
 * -----------------
 * This function is used to encapsulate the variables that are used by the
 * functions 'is_quotes' and 'expand_variable' and allow the functions to
 * share the same variables. 
 * 
 * @param: *ptr: The pointer to the argument.
 * @param: *segment: The pointer to the segment.
 * @param: *env: The pointer to the hashtable.
 * @param: state: The struct that contains the flags for the quotes.
 * @param: dollar: The struct that contains the flags for the dollar sign.
 * 
 */

typedef struct s_lex
{
	char				*ptr;
	char				*segment;
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
size_t					ft_strcspn(const char *str, char *delim1, char *delim2);
t_bool					is_whitespace(char c);

#endif