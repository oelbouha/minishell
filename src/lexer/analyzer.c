/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:24:14 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/13 13:55:08 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	and_or_errors(t_list *lst)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (!lst)
		return (1);
	if (node)
		return (ft_templatecmp(node->content, ">>:>:<<:<:(:||:&&:|", ':'));
	return (0);
}

int	opened_parentheses_errors(t_list *lst)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (node)
	{
		if (!ft_templatecmp(node->content, ">>:>:<<:<:(:||:&&:|", ':'))
			return (1);
	}
	return (0);
}

int	closed_parentheses_errors(t_list *lst)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (!lst)
		return (1);
	if (node)
	{
		return (ft_templatecmp(node->content, ">>:>:<<:<:(:||:&&:|", ':'));
	}
	return (0);
}

int check_unclosed_parentheses(t_list *lst)
{
	t_list	*curr;
	int		count;

	count = 0;
	curr = lst;
	while (curr != NULL)
	{
		if(ft_strcmp(curr->content, "(") == 0)
			count++;
		else if(ft_strcmp(curr->content, ")") == 0)
			count--;
		if (count < 0)
			return (1);
		curr = curr->next;
	}
	if (count != 0)
		return (1);
	return (0);
}

int analyse_last_node(t_list *lst, int err)
{
	t_list	*last;

	if (!lst)
		return (0);
	last = ft_lstlast(lst);
	if(check_unclosed_parentheses(lst) || check_unclosed_quotes(last->content))
	{
		msh_err("syntax error near unexpected token", last->content);
		return (1);
	}
	if (cant_be_last(last->content))
	{
		if (err != 2)
			msh_err("syntax error near unexpected token", last->content);
	}
	else
		return (0);
	while (last && cant_be_last(last->content))
		last = remove_last_node(&lst);
	return (1);
}

int	analyze_syntax(t_list *lst, char *token)
{
	int	err;

	if (!token)
		return (1);
	err = 0;
	if (ft_strcmp(token, "|") == 0)
		err = pipe_errors(lst);
	else if (ft_templatecmp(token, "<<:<:>>:>", ':'))
		err = redir_errors(lst);
	else if (BONUS && (!ft_strcmp(token, "||") || !ft_strcmp(token, "&&")))
		err = and_or_errors(lst);
	else if (BONUS && ft_strcmp(token, "(") == 0)
		err = opened_parentheses_errors(lst);
	else if (BONUS && ft_strcmp(token, ")") == 0)
		err = closed_parentheses_errors(lst);
	else
		err = simple_word_errors(lst);
	if (err == 1)
		return (msh_err("syntax error near unexpected token", token), 1);
	return (0);
}
