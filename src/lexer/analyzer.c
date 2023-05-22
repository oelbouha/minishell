/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:41:58 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 13:25:32 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
		stats->unclosed_quote = check_for_unclosed_quote(first->content);
	}
	else
		stats->syntax_error = 1;
}

int	check_errs(t_analyzer_stats stats, t_list **lst, t_list *prev, t_list *cur)
{
	if (stats.syntax_error || stats.unclosed_quote)
	{
		if (stats.syntax_error)
			print_syntax_error(cur);
		else
			print_quote_error(stats.unclosed_quote);
		if (prev)
			prev->next = NULL;
		else
			*lst = NULL;
		ft_lstclear(&cur, free);
		remove_last_if(lst, (t_lstcmp)cant_be_last);
		return (1);
	}
	else if (stats.heredoc_count > 16)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
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
	while ((cur || prev) && check_errs(stats, lst, prev, cur) == 0)
	{
		prev = cur;
		if (prev == NULL)
			return (0);
		cur = cur->next;
		check_pipe(prev, cur, &stats);
		check_redirs(prev, cur, &stats);
		check_word(prev, cur, &stats);
	}
	return (1);
}
