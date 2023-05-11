/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:41:58 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/11 17:02:58 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_error(t_list *cur)
{
	if (cur)
		msh_err("syntax error near unexpected token", cur->content);
	else
		ft_printf("-minishell: syntax error: unexpected end of file\n");
}

void	remove_last_if(t_list **lst, t_lstcmp cmp)
{
	t_list	*pre_last;

	if (lst == NULL || *lst == NULL)
		return ;
	while (1)
	{
		pre_last = *lst;
		while (pre_last->next && pre_last->next->next)
			pre_last = pre_last->next;
		if (pre_last->next == NULL && cmp(pre_last->content))
		{
			ft_lstdelone(pre_last, free);
			*lst = NULL;
			return ;
		}
		else if (pre_last->next && cmp(pre_last->next->content))
		{
			ft_lstdelone(pre_last->next, free);
			pre_last->next = NULL;
		}
		else
			return ;
	}
}
