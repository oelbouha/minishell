/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:27:11 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/15 23:12:46 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define BONUS 1

# include <unistd.h>
# include "minishell_types.h"
# include "lexer.h"
# include "core.h"
# include "../../gnl/get_next_line.h"

t_cmd		*new_simple_command(t_list *start, t_cmd_exec_cond cond);
t_cmd		*new_compound_command(t_list *start, t_cmd_exec_cond cond);
t_list		*new_file_redirection(char *filename, t_redir_type type);
t_list		*new_heredoc_redirection(char *raw_limiter);
int			read_heredoc(char *limiter);
char		*remove_quotes(char *arg);
char		*expand_var(char *str);
int			expand_fd_var(int fd);
char		*get_key(char *str);

#endif
