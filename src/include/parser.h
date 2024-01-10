/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:02:11 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/10 19:44:23 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./minishell.h"

void		tokenizer(t_hashtable *env, t_shell *shell);
void		skip_spaces(char **str);
int			isdelimiter(char *cmd);
t_tkn_list	*new_tkn_list(char *content, t_tkn_type type);
void		handle_token(char *str, t_shell *shell);
t_tkn_list	*last_tkn_list(t_tkn_list *tkn_list);
void		add_tkn_list(t_tkn_list *new_list, t_shell *shell);
void		parser(t_hashtable *env, t_shell *shell);
void		command_consistency(t_tkn_list *tokenized, t_shell *shell);
void		join_args(t_tkn_list *tkn_list, t_shell *shell);
void		add_cmd_list(t_shell *shell, t_cmd_list new_list);
t_cmd_list	*last_cmd_list(t_cmd_list *cmd_list);
int			tkn_list_size(t_tkn_list *tkn_list);
char		*tkn_type_converter(t_tkn_type type);
void		new_cmd_file_node(t_shell *shell, t_tkn_list **current);
void		new_redirect_node(t_shell *shell, t_tkn_list **current);
void		new_subshell_node(t_shell *shell, t_tkn_list **current);
void		new_operator_node(t_shell *shell, t_tkn_list **current);
int			is_expander(char x);
int			is_operator(t_tkn_type tkn);
int			crop_delimiter_tkn(char **cmd);
int			crop_quote_tkn(char **cmd);
void		free_tkn_list(t_tkn_list *tkn_list);
void		free_cmd_list(t_cmd_list *cmd_list);
t_cmd_list	*rewind_list(t_cmd_list **cmd_list);
void		set_io(t_cmd_list **cmd_list);
void		set_command_output(t_cmd_list **cmd_list, t_cmd_list *head);
void		set_command_input(t_cmd_list **cmd_list, t_cmd_list *head);
t_cmd_list	*find_command(t_cmd_list *cmd_list);
void		append_expand(t_shell *shell, t_tkn_list **current);
void		expand_all(t_shell *shell, t_hashtable *env);
int			is_redirect(t_tkn_type tkn);
void		free_lists(void);
int			is_redirect_op(char *cmd);
int			set_head_tail(t_tkn_list *tokenized, t_tkn_list	
				**head, t_tkn_list	**tail);
int			process_quote(char **cmd, char quote, t_bool *closed);
void		expand_iterator(char **cmd, int *i);

#endif