#ifndef SEGMENTS_H
#define SEGMENTS_H

#include <string>
#include <stdlib.h>

typedef struct s_segments
{
    char *str;
    struct s_segments *next;
}   t_segment; 

//############################### CREATE ###################################

t_segment *new_segments(char *str);

#endif