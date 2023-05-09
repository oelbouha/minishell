/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:41:58 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/09 14:44:55 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#define	OPERATORS "|:>:<:>>:<<:&&:||:(:)"
#define REDIRS ">:>>:<:<<"
#define CANT_BE_FIRST "|:&&:||:)"
#define CANT_BE_BEFORE_PIPE "|:>>:<<:>:<:&&:||:("
#define CANT_BE_BEFORE_LOGICAL_OPS "|:>>:<<:>:<:&&:||:("
#define CANT_BE_BEFORE_WORD ")"
#define CANT_BE_LAST "|:>:<:>>:<<:&&:||:("

void	check_logical_ops(t_list *prev, t_list *cur, t_analyzer_stats *stats)
{
	int	err;

	if (prev == NULL && cur == NULL)
		stats->syntax_error += 1;
	else if (prev && cur == NULL)
	{
		err = ft_templatecmp(prev->content, "&&:||", ':');
		stats->syntax_error += err;
	}
	else if (prev && ft_templatecmp(cur->content, "&&:||", ':'))
	{
		err = ft_templatecmp(prev->content, CANT_BE_BEFORE_LOGICAL_OPS, ':');
		stats->syntax_error += err;
	}
}

void	check_parentheses(t_list *prev, t_list *cur, t_analyzer_stats *stats)
{
	int	err;

	if (prev == NULL && cur == NULL)
		stats->syntax_error += 1;
	else if (prev && cur == NULL)
	{
		err = (ft_strcmp(prev->content, "(") == 0);
		stats->syntax_error += err;
	}
	else if (prev && ft_templatecmp(cur->content, "(:)", ':'))
	{
		if (ft_strcmp(cur->content, "(") == 0)
		{
			err = !ft_templatecmp(prev->content, "|:&&:||:(", ':');
			stats->parentheses_count++;
		}
		else
		{
			err = ft_templatecmp(prev->content, "|:>:>>:<<:<:&&:||:(", ':');
			stats->parentheses_count--;
			stats->cant_be_word = 1;
		}
		stats->syntax_error += err;
	}
}

void	check_pipe(t_list *prev, t_list *cur, t_analyzer_stats *stats)
{
	int	err;

	if (prev == NULL && cur == NULL)
		stats->syntax_error += 1;
	else if (prev && cur == NULL)
		stats->syntax_error += (ft_strcmp(prev->content, "|") == 0);
	else if (prev && ft_strcmp(cur->content, "|") == 0)
	{
		err = ft_templatecmp(prev->content, CANT_BE_BEFORE_PIPE, ':');
		stats->syntax_error += err;
	}
}

void	check_redirs(t_list *prev, t_list *cur, t_analyzer_stats *stats)
{
	if (prev == NULL && cur == NULL)
		stats->syntax_error += 1;
	else if (prev && cur == NULL)
		stats->syntax_error += ft_templatecmp(prev->content, REDIRS, ':');
	else if (prev && ft_templatecmp(cur->content, REDIRS, ':'))
	{
		stats->syntax_error += ft_templatecmp(prev->content, REDIRS, ':');
		stats->heredoc_count += (ft_strcmp(cur->content, "<<") == 0);
	}
}

void	check_word(t_list *prev, t_list *cur, t_analyzer_stats *stats)
{
	int	err;

	if (prev == NULL && cur == NULL)
		stats->syntax_error += 1;
	else if (prev && cur && !ft_templatecmp(cur->content, OPERATORS, ':'))
	{
		err = stats->cant_be_word;
		err = err && !ft_templatecmp(prev->content, REDIRS, ':');
		if (ft_strlen(CANT_BE_BEFORE_WORD))
			err += ft_templatecmp(prev->content, CANT_BE_BEFORE_WORD, ':');
		stats->syntax_error += err;
	}
}

void	print_error(t_list *prev, t_list *cur)
{
	if (cur)
		msh_err("syntax error near unexpected token", cur->content);
	else
		msh_err("syntax error near unexpected token", prev->content);
}

int	_cant_be_last(char *token)
{
	return (ft_templatecmp(token, CANT_BE_LAST, ':'));
}

void	remove_last_if(t_list **lst, t_lstcmp cmp)
{
	t_list	*pre_last;

	if (lst == NULL || *lst == NULL)
		return ;
	while (1)
	{
		pre_last = *lst;
		while (pre_last->next->next)
			pre_last = pre_last->next;
		if (pre_last->next == NULL && cmp(pre_last->content))
		{
			ft_printf("-deleting [%s]\n", pre_last->content);
			ft_lstdelone(pre_last, free);
			*lst = NULL;
			return ;
		}
		else if (pre_last->next && cmp(pre_last->next->content))
		{
			ft_printf("deleting [%s]\n", pre_last->next->content);
			ft_lstdelone(pre_last->next, free);
			pre_last->next = NULL;
		}
		else
			return ;
	}
}

int	check_first_node(t_list *first)
{
	if (first)
		return (ft_templatecmp(first->content, CANT_BE_FIRST, ':'));
	return (1);
}

/*
 *	parentheses count
 *	enclosed quotes
 *	word after parentheses redirs
 *
 */
int	analyze(t_list **lst)
{
	t_analyzer_stats	stats;
	t_list				*cur;
	t_list				*prev;

	prev = NULL;
	cur = *lst;
	ft_bzero(&stats, sizeof(t_analyzer_stats));
	stats.syntax_error = check_first_node(cur);
	while (stats.syntax_error == 0 && (cur || prev))
	{
		prev = cur;
		if (prev == NULL)
			break ;
		cur = cur->next;
		check_pipe(prev, cur, &stats);
		check_redirs(prev, cur, &stats);
		check_logical_ops(prev, cur, &stats);
		check_parentheses(prev, cur, &stats);
		check_word(prev, cur, &stats);
	}
	if (stats.syntax_error)
	{
		ft_printf("error\n");
		print_error(prev, cur);
		prev->next = NULL;
		ft_lstclear(&cur, free);
		remove_last_if(lst, (t_lstcmp)_cant_be_last);
		return (1);
	}
	else if (stats.heredoc_count > 16)
	{
		ft_lstclear(lst, free);
		*lst = NULL;
		return (1);
	}
	return (0);
}
