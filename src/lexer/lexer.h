/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:14:18 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/20 12:16:19 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include <readline/history.h>
# include <dirent.h>

# define OPERATORS "|:>:<:>>:<<"
# define REDIRS ">:>>:<:<<"
# define CANT_BE_FIRST "|"
# define CANT_BE_BEFORE_PIPE "|:>>:<<:>:<"
# define CANT_BE_LAST "|:>:<:>>:<<"

typedef struct s_analyzer_stats	t_analyzer_stats;

# ifndef LEXER_BONUS_H

struct s_analyzer_stats
{
	int		syntax_error;
	int		heredoc_count;
	char	unclosed_quote;
};

# endif

//	Tokenizer
int		get_token_length(const char *line);
int		get_word_length(const char *line);
int		is_word_delimiter(const char *line);

void	check_pipe(t_list *prev, t_list *cur, t_analyzer_stats *stats);
void	check_redirs(t_list *prev, t_list *cur, t_analyzer_stats *stats);
void	check_word(t_list *prev, t_list *cur, t_analyzer_stats *stats);
char	check_for_unclosed_quote(char *token);

void	print_syntax_error(t_list *cur);
void	print_quote_error(const char quote);
void	remove_last_if(t_list **lst, t_lstcmp cant_be_last);

void	configure_readline(void);

#endif
