/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:32:11 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/04 16:55:09 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "./minishell.h"

//################################ INIT ######################################//

void	init_exec_vector(t_exec *exec);
t_bool	is_builtin(t_ast *node);
int		execute_builtin(t_hashtable *hashtable, t_ast *node);
void	init_redirects(t_exec *exec);
int		handle_redirects(t_ast *node);
int		create_files(t_ast *node, t_exec *exec, int option);

//############################# REDIRECTIONS #################################//

int		redirect_input(t_ast *node, char *filename);
int		redirect_output(t_ast *node, char *filename);
int		redirect_append(t_ast *node, char *filename);
int		get_index_redirect(t_ast *root, t_type type);
void	redirect_fds(t_ast *node);
int		analyze_redirect(t_exec *exec, t_hashtable *hashtable, t_ast *node);
void	simple_redirect(t_exec *exec, t_hashtable *hash, t_ast *node);
int		handle_heredoc(t_hashtable *hash, t_exec *exec, t_ast *node);
char	*check_expansion(t_hashtable *env, char **line, size_t *len);
t_bool	verify_file_permissions(const char *file);
int		verify_cmd_permissions(const char *cmd);

//############################# OPERATOR #####################################//

void	handle_pipes(t_hashtable *hash, t_exec *exec, t_ast *node,
			int *prev_pipe);
void	handle_other(t_exec *exec, t_hashtable *hash, t_ast *node,
			int *prev_pipe);
void	execute_pipes(t_exec *exec, t_ast *node, int *prev_pipe,
			int *next_pipe);
void	handle_logical(t_exec *exec, t_hashtable *hash, t_ast *node);
void	simple_logical(t_exec *exec, t_hashtable *hash, t_ast *node,
			int status);

//############################# PREPARE_EXEC #################################//

void	backup_fd(int *old_stdin, int *old_stdout);
void	restore_fd(int reset_stdin, int reset_stdout);
char	*build_cmd_path(t_ast *node, char *path);
void	handle_error(t_ast *node, int result);
void	analyze_if_print(t_ast *node, int index);
int		analyze_cmd(t_hashtable *hashtable, t_ast *node);
int		analyze_heredoc(t_exec *exec, t_ast *node, t_hashtable *hashtable);
char	*generate_filename(int count_hdoc);
void	next_is_rdir(t_exec *exec, t_hashtable *hash, t_ast *node,
			char *filename);
void	next_is_pipe(t_exec *exec, t_hashtable *hash, t_ast *node,
			char *filename);
void	parent_hdoc(t_exec *exec, t_hashtable *hash, t_ast *node,
			int *next_pipe);

//############################# EXECUTION ####################################//

void	redirect_out(t_exec *exec, t_hashtable *hash, t_ast *node);
int		exec_simple(t_hashtable *hash, t_exec *exec, t_ast *node);
int		exec_multi_cmds(t_exec *exec, t_hashtable *hashtable, t_ast *root);
int		forking(t_exec *exec, t_hashtable *hash, t_ast *node);
int		exec_forked_cmd(t_exec *exec, t_hashtable *hash, t_ast *node);
int		wait_for_children(t_ast *node);
void	close_all_fds(void);

//############################# UTILS ########################################//

void	free_for_finish(t_exec *exec, t_hashtable *env);
void	ft_printf_fd(int fd); // Remover ao finalizar

#endif