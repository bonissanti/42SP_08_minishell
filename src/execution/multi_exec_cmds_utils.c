/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:35:32 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/07 14:54:13 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"
#include "../include/hash.h"
#include "../include/builtins.h"
#include "../include/segments.h"

// t_ast *branch_tip(t_ast *node)
// {
// 	t_ast *first;

// 	if(!node)
// 		return (NULL);
// 	first = node;
// 	if(first->left == NULL)
// 		return (first);
// 	else
// 	{
// 		while(first->left)
// 			first = first->left;
// 	}
// 	return(first);
// }

void ft_printf_fd(int fd)
{
    char *line;

    line = get_next_line(fd);
    if (!line)
    {
        ft_fprintf(2, "fd didn't have any lines to print.\n");
        return ;
    }
    while(line)
    {
        ft_fprintf(2, "es: %s", line);
        line = get_next_line(fd);
    }
    ft_fprintf(2, "____________________\n");
}

int is_logical(char *operator)
{
	if(!ft_strncmp(operator, "&&", 2) || !ft_strncmp(operator, "||", 2))
		return (true);
	return(false);
}

int check_redirect_type(char *operator)
{
	if (ft_strncmp(operator, "<<", 2) && *operator == '<')
		return (1);
	else if(!ft_strncmp(operator, ">>", 2) || *operator == '>')
		return (2);
	else
		return (0);
}
