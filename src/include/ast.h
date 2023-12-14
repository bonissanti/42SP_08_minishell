/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:46:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/14 17:31:42 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "./minishell.h"

//############################### AST #########################################

t_ast 				*create_node(t_cmd_list *cmd_list, t_hashtable *env);
void 				insert_ast(t_ast **head, t_ast *new_node, t_exec *exec);
void				delete_node(t_ast *head);
void				pre_order_traversal(t_ast *head); // Remover depois
t_ast				*init_ast(t_cmd_list *cmd_list, t_exec *exec, t_hashtable *env);

//############################### UTILS #######################################

char	**ast_split(char const *s, char c);

#endif