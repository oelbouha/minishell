/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:41:58 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/11 15:27:18 by ysalmi           ###   ########.fr       */
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
	}
	else
		stats->syntax_error = 1;
}

int	check_errors(t_analyzer_stats stats, t_list **lst, t_list *prev, t_list *cur)
{
	if (stats.unclosed_quote)
	{
		ft_printf("-minishell: unexpected EOF while looking for matching `%c'\n",
				stats.unclosed_quote);
		ft_printf("-minishell: syntax error: unexpected end of file\n");
		if (prev)
			prev->next = NULL;
		ft_lstdelone(cur, free);
		remove_last_if(lst, (t_lstcmp)cant_be_last);
		return (1);
	}
	else if (stats.syntax_error || stats.parentheses_count < 0)
	{
		print_error(cur);
		if (prev)
			prev->next = NULL;
		else
			*lst = NULL;
		ft_lstclear(&cur, free);
		remove_last_if(lst, (t_lstcmp)cant_be_last);
		return (1);
	}
	else if (stats.parentheses_count && !cur)
	{
		ft_printf("-minishell: syntax error: unexpected end of file\n");
		ft_lstclear(lst, free);
		*lst = NULL;
		return (1);
	}
	else if (stats.heredoc_count > 16)
	{
		ft_printf("-minishell: maximum here-document count exceeded\n");
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
	while (check_errors(stats, lst, prev, cur) == 0 && (cur || prev))
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
