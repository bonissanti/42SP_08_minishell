#include "../include/hash.h"
#include "../include/temp.h"
#include "../include/segments.h"


void init_structs(void *structs, size_t struct_size)
{
	memset(structs, 0, sizeof(struct_size));
}

// t_files *create_file(char *name)
// {
//     t_files *new_file;

//     new_file = malloc(sizeof(t_files));

// 	new_file->content = ft_strdup(name);
// 	new_file->next = NULL;
// 	free(name);
// 	return (new_file);
// }

// void add_file(t_files **head, char *name)
// {
// 	t_files *new_file;
// 	t_files *current;

// 	new_file = create_file(name);
// 	if (*head == NULL)
// 		*head = new_file;
// 	else
// 	{
// 		current = *head;
// 		while (current->next)
// 			current = current->next;
// 		current->next = new_file;
// 	}
// }