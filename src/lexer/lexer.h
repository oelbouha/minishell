/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:14:18 by ysalmi            #+#    #+#             */
/*   Updated: 2023/03/23 13:25:35 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/errno.h>
# include "../../libft/inc/libft.h"

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define SPACE 32
# define TAB 9

typedef unsigned long long	t_ull;

char		*get_input(t_ull state);
void		configure_readline(void);
int			word_len(char *str);
int			handle_quotes(t_list **lst, char *str, int *err);
int			handle_redir_and_pipe(t_list **lst, char *str, int *err);
t_list		*split_line(char *line);

#endif


