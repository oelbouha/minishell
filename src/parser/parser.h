/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:27:11 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/04 17:41:15 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define NO_REDIRS (t_list *)-1

# include <unistd.h>
# include <dirent.h>
# include "minishell_types.h"
# include "lexer.h"
# include "core.h"
# include "../../gnline/get_next_line.h"

t_list		*new_command(t_list **head, t_cmd_exec_cond cond);
int			get_commands_count(t_list *start);
t_list		*get_next_cmd(t_list **head);
void		destroy_command(t_cmd *cmd);

t_list		*new_simple_command(t_list **head, t_cmd_exec_cond cond);
void		destroy_simple_command(t_cmd *command);

t_list		*new_compound_command(t_list **head, t_cmd_exec_cond cond);
t_list		*new_subshell_command(t_list **start, t_cmd_exec_cond cond);
void		destroy_compound_command(t_cmd *command);

t_list		*get_cmd_redirs(t_list **head);
int			add_redirection(t_list **redirs, t_list **head);
t_redir		*new_file_redirection(char *filename, t_redir_type type);
t_redir		*new_heredoc_redirection(char *raw_limiter);
int			is_heredoc(t_redir *redir);
void		del_heredoc(t_redir *redir);
void		destroy_redir(t_redir *redir);
int			read_heredoc(char *limiter);

char		*remove_quotes(char *arg);
char		*expand_var(char *str);
int			expand_heredoc(int fd);
int			is_invalid_key(const char *key);
char		*get_key(char *str);
t_list		*expand_wildcard(char *line);
char		*split_expanded(char *expanded);
int			should_expand_wildcard(char *line);

int			is_redirection(const char *token);
int			is_an_operator(const char *token);
t_list		*move_node(t_list **to, t_list *node, t_list *prev);

#endif
