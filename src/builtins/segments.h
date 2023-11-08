#ifndef SEGMENTS_H
#define SEGMENTS_H

// #include <string>
#include <stdlib.h>
#include "env.h"

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

//############################### CREATE ###################################

t_segment *new_segments(char *str);
void parse_quotes(t_hashtable *env, char **args);
void process_segment(t_quote *quote, t_segment *head, size_t len);
size_t ft_strcspn(const char *str, char *delim1, char *delim2);
size_t is_even_quotes(char *str);


#endif