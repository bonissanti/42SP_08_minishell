#ifndef SEGMENTS_H
# define SEGMENTS_H

// #include <string>
# include "../builtins/env.h"
# include <stdlib.h>

typedef struct s_segments
{
	char				*str;
	struct s_segments	*next;
}						t_segment;

typedef struct s_quote_state
{
	t_bool				single_open;
	t_bool				double_open;
}						t_quote_state;

// typedef struct s_quote
// {
//     char        *ptr;
//     char        *segment;
//     int         type;
//     int         prev_type;
//     t_hashtable *env;
//     t_bool      is_squote_open;
//     t_bool      is_dquote_open;
//     size_t      len;
//     t_segment   *head;
// }   t_quote;

typedef struct s_quote
{
	char				*ptr;
	char				*segment;
	int					type;
	int					prev_type;
	t_hashtable			*env;
	t_quote_state		state;
}						t_quote;

//############################### LIST ###################################

t_segment				*new_segments(char *str);
void					add_segments(t_segment **head, char *str);
char					*join_segments(t_segment *head);
void					free_segments(t_segment *head);

//############################ PARSE/QOUTES ###############################

// t_parse                 *init_parse(t_hashtable *env, char *arg);
// t_quote init_quote(t_hashtable *env, char *args);
char					get_quote_type(char c);
size_t					even_close_quotes(char *str);
// void                    handle_quotes(t_parse *quote, t_quote_state *status);
// void   					add_char_to_segment(t_parse *parse, t_segment **head, t_quote_state *status, size_t *len);
// void                    expand_variable(t_parse *parse, t_segment **head, size_t *len);
void					parse_quotes(t_hashtable *env, char **args);
void	expand_variable(t_quote *quote, t_segment **head, size_t len);
t_quote *init_quote(t_hashtable *env, char *arg);

//############################### UTILS ###################################

size_t					ft_strcspn(const char *str, char *delim1, char *delim2);
t_bool					is_whitespace(char c);

#endif