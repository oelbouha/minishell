/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:41:58 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/07 10:23:20 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#define LEXER_PIPE ">>:<<:>:<"

int	check_pipe(t_list *prev, t_list *cur)
{
	if (prev == NULL && cur == NULL)
		return (1);
	else if (prev && cur == NULL)
		return (ft_strcmp(prev->content, "|") == 0)
	else if (ft_strcmp(cur->content, "|") == 0)
	{
		if (prev == NULL)
			return (1);
		return (ft_templatecmp(cur->content, LEXER_PIPE, ':'))
	}
	else
		return (0);
}


int	analyze_syntax(t_list *lst)
{
	int		err;
	t_list	*prev;

	err = 0;
	prev = NULL;
	while (lst)
	{
		err += check_pipe(prev, lst);
		prev = lst;
		lst = lst->next;
	}
}
