/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:27:11 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/15 17:59:53 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include "minishell.h"
# include "minishell_types.h"

int			get_commands_count(t_list *start);
t_list		*get_next_cmd(t_list **head);

t_list		*new_simple_command(t_list **head, t_cmd_exec_cond cond);
void		destroy_simple_command(t_cmd *command);

t_list		*new_compound_command(t_list **head, t_cmd_exec_cond cond);
t_list		**get_commands_arr(t_list **head, int count);
void		destroy_compound_command(t_cmd *command);

t_list		*get_cmd_redirs(t_list **head);
int			add_redirection(t_list **redirs, t_list **head);
t_redir		*new_file_redirection(char *filename, t_redir_type type);
t_redir		*new_heredoc_redirection(char *raw_limiter);
int			is_heredoc(t_redir *redir);
void		del_heredoc(t_redir *redir);
void		destroy_redir(t_redir *redir);
int			read_heredoc(char *limiter);


/*+++++++++++++++++++++++++++  expand functions +++++++++++++++++++++++++++++*/

char		*remove_quotes(char *arg);
char		*expand_var(char *str);
char		*get_key(char *str);
char		*remove_quotes_and_get_expanded(char *content);
char		*get_key(char *str);
char		**convert_list_to_array(t_list	*lst);

int			expand_heredoc(int fd);
int			is_invalid_key(const char *key);
int			remove_quotes_and_expand(t_list **prev, t_list **lst, t_list **new_lst);
int			should_expand(char *str);
int			needs_spliting(char *str);
int			get_length(char **arr);
int			should_expand_wildcard(char *line);
int			is_invalid_key(const char *key);
int			get_expanded_length(char *str);
int			quotes_len(char *str);
int			get_key_len(char *str);

t_list		*split_content(char *line);
t_list		*get_expanded(t_list *lst);
t_list		*expand(t_list *cur, t_list *prev, t_list **lst_ptr);
t_list		*expand_wildcard(char *line);
t_list		*split_and_join(t_list *lst);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int			is_redirection(const char *token);
int			is_an_operator(const char *token);
t_list		*move_node(t_list **to, t_list *node, t_list *prev);

#endif
