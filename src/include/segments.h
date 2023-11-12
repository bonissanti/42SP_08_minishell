#ifndef SEGMENTS_H
#define SEGMENTS_H

// #include <string>
#include <stdlib.h>
#include "../builtins/env.h"

typedef struct s_segments
{
    char *str;
    struct s_segments *next;
}   t_segment; 

typedef struct s_quote
{
    char        *ptr;
    char        *segment;
    int         type;
    int         prev_type;
    t_hashtable *env;
}   t_quote;

//############################### LIST ###################################

t_segment *new_segments(char *str);
void add_segments(t_segment **head, char *str);
char *join_segments(t_segment *head);
void	free_segments(t_segment *head);

//############################### QUOTES ###################################

char get_quote_type(char c);
size_t even_close_quotes(char *str);
void parse_quotes(t_hashtable *env, char **args);

//############################### UTILS ###################################

size_t ft_strcspn(const char *str, char *delim1, char *delim2);
t_bool	is_whitespace(char c);

#endif