/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:27:11 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/13 17:34:44 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define BONUS 1

# include <unistd.h>
# include "minishell_types.h"

t_cmd		*new_simple_command(t_list *start, t_cmd_exec_cond cond);
t_list		*new_file_redirection(char *filename, t_redir_type type);
t_list		*new_heredoc_redirection(char *raw_limiter);
char		*remove_quotes(char *arg);

#endif
