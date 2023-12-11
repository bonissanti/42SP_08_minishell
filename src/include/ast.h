/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:46:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/10 19:20:14 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "../../minishell.h"

//############################### AST #########################################

t_ast 				*create_node(t_cmd_list *cmd_list);
void 				insert_ast(t_ast **head, t_ast *new_node, t_exec *exec);
void				delete_node(t_ast *head);
void				pre_order_traversal(t_ast *head); // Remover depois

//############################### UTILS #######################################

char	**ast_split(char const *s, char c);

#endif