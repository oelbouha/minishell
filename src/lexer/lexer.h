/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:14:18 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/13 12:20:45 by ysalmi           ###   ########.fr       */
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
# define BONUS 1
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
char		*read_line(t_ull state);
int			word_len(char *str);
int			is_and_or(char *str);
void		print_error_msg(char *token);
int			handle_quotes(char *str);
int			handle_redir_and_pipe(char *str);
int			simple_word(char *str);
int			push_token_to_list(t_list **lst, char *token);
int			analyze_syntax(t_list *lst, char *token);
int			word_len(char *str);
int			is_redir(char *token);
int			is_operator(char c, char s);
int			cmp(char *str, char *template);
int			check_unclosed_quotes(char *line);
int			cant_be_last(char *token);
int			get_token_len(char *line);
char		*get_token(char *str, int *err);
int			analyse_last_node(t_list *lst, int err);
t_list		*split_line(char *line);
t_list		*remove_last_node(t_list **lst);

/*							error functions
=============================================================================
*/
int			redir_errors(t_list *lst);
int			simple_word_errors(t_list *lst);
int			pipe_errors(t_list *lst);

#endif


