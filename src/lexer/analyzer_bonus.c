/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:41:58 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/11 21:48:41 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_bonus.h"

static int	cant_be_last(char *token)
{
	return (ft_templatecmp(token, CANT_BE_LAST, ':'));
}

void	check_first_node(t_list *first, t_analyzer_stats *stats)
{
	int	err;

	if (first)
	{
		err = ft_templatecmp(first->content, CANT_BE_FIRST, ':');
		stats->syntax_error = err;
		stats->heredoc_count += ft_strcmp(first->content, "<<") == 0;
		stats->parentheses_count += ft_strcmp(first->content, "(") == 0;
		stats->unclosed_quote = check_for_unclosed_quote(first->content);
	}
	else
		stats->syntax_error = 1;
}

int	check_errs(t_analyzer_stats s, t_list **lst, t_list *prev, t_list *cur)
{
	if (s.syntax_error || s.parentheses_count < 0 || s.unclosed_quote)
	{
		if (s.syntax_error)
			print_syntax_error(cur);
		else
			print_quote_error(s.unclosed_quote);
		if (prev)
			prev->next = NULL;
		else
			*lst = NULL;
		ft_lstclear(&cur, free);
		remove_last_if(lst, (t_lstcmp)cant_be_last);
		return (1);
	}
	else if ((s.parentheses_count && !cur) || s.heredoc_count > 16)
	{
		if (s.heredoc_count > 16)
			msh_err("-minishell: maximum here-document count exceeded", 0);
		else
			msh_err("-minishell: syntax error: unexpected end of file", 0);
		ft_lstclear(lst, free);
		*lst = NULL;
		return (1);
	}
	return (0);
}

int	analyze(t_list **lst)
{
	t_analyzer_stats	stats;
	t_list				*cur;
	t_list				*prev;

	prev = NULL;
	cur = *lst;
	ft_bzero(&stats, sizeof(t_analyzer_stats));
	check_first_node(cur, &stats);
	while (check_errs(stats, lst, prev, cur) == 0 && (cur || prev))
	{
		prev = cur;
		if (prev == NULL)
			return (0);
		cur = cur->next;
		if (cur && ft_templatecmp(cur->content, "|:&&:||", ':'))
			stats.cant_be_word = 0;
		check_pipe(prev, cur, &stats);
		check_redirs(prev, cur, &stats);
		check_logical_ops(prev, cur, &stats);
		check_parentheses(prev, cur, &stats);
		check_word(prev, cur, &stats);
	}
	return (1);
}
