/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:02:41 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 11:33:57 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H


#define EMPTY_VAR (char *)-1

# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "minishell.h"
# include "minishell_types.h"
# include "core_internal.h"
# include "../gnline/get_next_line.h"

int	execute_simple_command(t_cmd *cmd, t_bool force_fork, t_bool wait_child);
int	execute_compound_command(t_cmd *cmd);
int	execute_subshell_command(t_cmd *cmd, t_bool wait_child);
int	prep_redirs(t_list *redirs);

int	get_exit_status(pid_t pid);

char		*remove_quotes(char *arg);
char		*expand_var(char *str);
char		*get_key(char *str);
char		*get_key(char *str);
char		**convert_lst_to_array(t_list	*lst);
void		print_error_msg(char *cmd_name, char *msg, int exit_status);

int			expand_heredoc(int fd);
int			is_invalid_key(const char *key);
char		*remove_quotes_and_expand(char *content);
int			should_expand(char *str);
int			needs_spliting(char *str);
int			arr_length(char **arr);
int			should_expand_wildcard(char *line);
int			is_invalid_key(const char *key);
int			get_expanded_length(char *str);
int			quotes_len(char *str);
int			get_key_len(char *str);
int			check_cmd_path(char *cmd);
int			command_not_found(char *cmd_name);


t_list		*expand(t_list *lst);
t_list		*split_content(char *line);
t_list		*get_expanded(char *content);
// void		expand(t_list *cur, t_list *prev, t_list **lst_ptr);
t_list		*expand_wildcard(char *line);
char	*expand_and_join(t_list *lst);
char	**convert_lst_to_array(t_list *lst);

char		*get_cmd_path(char *cmd_name);

#endif
