/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:14:18 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/11 15:54:09 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef READER_H
#  define READER_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/errno.h>
# include "core.h"

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define BONUS 0
# ifndef SPACE
#  define SPACE ' '
# endif
# ifndef TAB
#  define TAB '\t'
# endif

typedef unsigned long long	t_ull;

void		print(t_list *lst);
void		configure_readline(void);
void		free_lst_content(void *content);
char		*get_input(t_ull state);
int			word_len(char *str);
int			handle_quotes(t_list **lst, char *str, int *err);
int			handle_redir_and_pipe(t_list **lst, char *str, int *err);
int			simple_word(t_list **lst, char *str, int *err);
int			word_len(char *str);
int			is_operator(char c, char s);
t_list		*split_line(char *line);

#endif


