/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:27:11 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/01 09:44:08 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define BONUS 1
# define NO_REDIRS (t_list *)-1

# include <unistd.h>
# include "minishell_types.h"
# include "lexer.h"

t_list		*new_command(t_list **head, t_cmd_exec_cond cond);
int			get_commands_count(t_list *start);
t_list		*get_next_cmd(t_list **head);
void		destroy_command(t_cmd *cmd);

t_list		*new_simple_command(t_list **head, t_cmd_exec_cond cond);
void		destroy_simple_command(t_cmd *command);

t_list		*new_compound_command(t_list **head, t_cmd_exec_cond cond);
void		destroy_compound_command(t_cmd *command);

t_list		*get_cmd_redirs(t_list **head);
t_redir		*new_file_redirection(char *filename, t_redir_type type);
t_redir		*new_heredoc_redirection(char *raw_limiter);
void		destroy_redir(t_redir *redir);
int			read_heredoc(char *limiter);

char		*remove_quotes(char *arg);

int			is_redirection(const char *token);
int			is_an_operator(const char *token);
t_list		*move_node(t_list **to, t_list *node, t_list *prev);

#endif
