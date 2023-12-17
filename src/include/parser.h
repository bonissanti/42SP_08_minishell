/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:02:11 by aperis-p          #+#    #+#             */
/*   Updated: 2023/12/15 15:21:00 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

#include "./minishell.h"

void		tokenizer(t_global *g_global, char *cmd, t_hashtable *env);
void 		skip_spaces(char **str);
int			isdelimiter(char *cmd);
t_tkn_list	*new_tkn_list(char *content, t_tkn_type type);
void	    handle_token(t_global *g_global, char *str);
t_tkn_list	*last_tkn_list(t_tkn_list *tkn_list);
void		add_tkn_list(t_global *g_global, t_tkn_list *new_list);
void		print_tkn_list(t_tkn_list *tkn_list);   //DELETE THIS BEFORE DELIVERY 
void		print_cmd_list(t_cmd_list *cmd_list);	//DELETE THIS BEFORE DELIVERY
char		*tkn_type_string(t_tkn_type type);      //DELETE THIS BEFORE DELIVERY
int         parser(t_hashtable *env);
int			command_consistency(t_tkn_list *tokenized);
int			handle_redirect(t_tkn_type tkn);
void		join_args(t_tkn_list *tkn_list);
void		add_cmd_list(t_cmd_list new_list);
t_cmd_list	*last_cmd_list(t_cmd_list *cmd_list);
int			tkn_list_size(t_tkn_list *tkn_list);
char		*cmd_type_string(t_type type);
void		print_cmd_list(t_cmd_list *cmd_list);
void		print_tkn_list(t_tkn_list *tkn_list);
char		*tkn_type_converter(t_tkn_type type);
void		new_cmd_file_node(t_tkn_list **current);
void		new_redirect_node(t_tkn_list **current);
void		new_subshell_node(t_tkn_list **current);
void		new_operator_node(t_tkn_list **current);
int			is_expander(char x);
char		*append_expanded(char *cmd, char **exp, t_hashtable *env, int index);
int			is_operator(t_tkn_type tkn);
int			crop_delimiter_tkn(char **cmd);
void		free_tkn_list(t_tkn_list *tkn_list);
void		free_cmd_list(t_cmd_list *cmd_list);
t_cmd_list	*rewind_list(t_cmd_list **cmd_list);
void		set_io(t_cmd_list **cmd_list);
void		set_command_output(t_cmd_list **cmd_list, t_cmd_list *head);
void		set_command_input(t_cmd_list **cmd_list, t_cmd_list *head);
t_cmd_list	*find_command(t_cmd_list *cmd_list);
void		append_expand(t_tkn_list **current);
void		expand_all(t_tkn_list *tkn_list, t_hashtable *env);
int			is_redirect(t_tkn_type tkn);
void		free_lists(t_tkn_list *tkn_list, t_cmd_list *cmd_list);

#endif