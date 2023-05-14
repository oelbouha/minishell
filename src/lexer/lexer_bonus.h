/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:14:04 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/11 17:54:40 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_BONUS_H
# define LEXER_BONUS_H

# include "lexer.h"

# undef OPERATORS
# define OPERATORS "|:>:<:>>:<<:&&:||:(:)"

# undef CANT_BE_FIRST
# define CANT_BE_FIRST "|:&&:||:)"

# undef CANT_BE_BEFORE_PIPE
# define CANT_BE_BEFORE_PIPE "|:>>:<<:>:<:&&:||:("

# undef CANT_BE_LAST
# define CANT_BE_LAST "|:>:<:>>:<<:&&:||:("

struct s_analyzer_stats
{
	int		syntax_error;
	int		heredoc_count;
	char	unclosed_quote;
	int		parentheses_count;
	int		cant_be_word;
};

void	check_logical_ops(t_list *prev, t_list *cur, t_analyzer_stats *stats);
void	check_parentheses(t_list *prev, t_list *cur, t_analyzer_stats *stats);
void	check_word(t_list *prev, t_list *cur, t_analyzer_stats *stats);

#endif
