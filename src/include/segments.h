#ifndef SEGMENTS_H
# define SEGMENTS_H

#include "./minishell.h"

//############################### INIT ###################################

void init_structs(void *structs, int type, size_t struct_size);

//############################### LIST ###################################

t_segment				*new_segments(char *str);
void					add_segments(t_segment **head, char *str);
char					*join_segments(t_segment *head);
void					free_segments(t_segment *head);

//############################### QUOTES ###################################

t_lex					*init_lex(t_hashtable *env, char *arg);
t_quote_bool			init_quote_bool(void);
size_t					even_close_quotes(char *str);
void					analyzing_quotes(t_hashtable *env, char **args);
void					handle_quotes(t_hashtable *env, t_segment *head, char **args);
void					final_process(t_lex *quote, t_segment **head,
							char **args, size_t *len);

//############################### DOLLAR ###################################

void					expand_variable(t_lex *quote, t_segment **head,
							size_t *len);
t_expand				init_expand_dollar(void);

//############################### TILDE ###################################

void					expand_tilde(t_hashtable *hashtable, char *str);

//############################### UTILS ###################################

void					error_close_quotes(t_lex *quote);
t_bool					check_dollar_space(char *str);
t_bool					check_handle_error(t_lex *quote, int i);
char					*ft_strndup(const char *str, size_t num);
size_t					custom_strcspn(const char *str, char *delim1);
t_bool					is_whitespace(char c);
size_t 					ft_strcspn(const char *str, char *delim1);

//############################### WILDCARD ###################################

char					*handle_wildcard(char *pattern);
char					*ft_strtok(char *str, const char *delim);
void 					finish_wildcard(t_segment *head, t_file *file);
char					*generate_results(t_segment *segments, t_file *file);

#endif