#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

/**
 * Function: template
 * -----------------
 * This function sorts a list of 3 numbers. It first checks if the list is
 * already sorted, if it is, it returns. If it is not, it checks the possible
 * combinations of the numbers and swaps or rotates them accordingly.
 * 
 * @param: **head: pointer to the head of the list.
 * @param: size: size of the list.
 * @var: a, b, c: values of the first, second and third node of the list.
 * 
 * @return: This is a void function, so it does not return a value.
 *
 */
