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

int	pipe_errors(t_list *lst)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (!lst)
		return (1);
	if (node)
		return (ft_templatecmp(node->content, ">>:>:<<:<:(:):||:&&", ':'));
	return (0);
}

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
		if (ft_templatecmp(node->content, ">>:>:<<:<:)", ':'))
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
		return (ft_templatecmp(node->content, ">>:>:<<:<:(:||:&&:|", ':'));
	return (0);
}

int	redir_errors(t_list *lst)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (node)
		return (ft_templatecmp(node->content, ">>:>:<<:<", ':'));
	return (0);
}

int	simple_word_errors(t_list *lst)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (node)
		if (ft_strcmp(node->content, ")") == 0)
			return (1);
	return (0);
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
	{
		msh_err("syntax error near unexpected token", token);
		return (1);
	}
	return (0);
}
