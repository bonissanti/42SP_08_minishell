/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:46:10 by brunrodr          #+#    #+#             */
/*   Updated: 2023/12/29 21:09:28 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "./minishell.h"

//############################### AST #########################################

t_ast	*init_ast(t_cmd_list *cmd_list, t_exec *exec);
void	prepare_ast(t_ast *new_node, t_cmd_list *cmd_list);
t_ast	*create_node(t_cmd_list *cmd_list);
void	insert_ast(t_ast **head, t_ast *new_node, t_exec *exec);
void	delete_node(t_ast *head);
t_ast	*find_node(t_ast *root, t_type type);

//############################### UTILS #######################################

char	**ast_split(char *s, char c);

#endif