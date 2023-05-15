/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:07:46 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/11 22:07:48 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

t_list	*not_a_valid_key(t_list *prev, t_list **cur)
{
	ft_lstdel_first(cur, free);
	if (prev)
		prev->next = *cur;
	return (prev);
}

t_list	*expand(t_list *cur, t_list *prev, t_list **lst_ptr)
{
	t_list	*lst;
	t_list	*temp;

	lst = split_content(cur->content);
	lst = split_and_join(lst);
	if (lst == NULL)
		return (ft_lstclear(&cur, free), NULL);
	if (lst == EMPTY_LST)
		return (not_a_valid_key(prev, &cur));
	if (prev)
	{
		temp = cur->next;
		prev->next = lst;
	}
	else
	{
		*lst_ptr = lst;
		temp = cur->next;
	}
	prev = ft_lstlast(lst);
	prev->next = temp;
	ft_lstdel_first(&cur, free);
	return (prev);
}

t_list	*get_expanded(t_list *lst)
{
	t_list	*cur;
	t_list	*prev;

	prev = NULL;
	cur = lst;
	while (cur)
	{
		if (should_expand(cur->content))
		{
			prev = expand(cur, prev, &lst);
			if (prev == NULL)
				return (NULL);
			cur = prev->next;
		}
		else
		{
			cur->content = remove_quotes(cur->content);
			prev = cur;
			cur = cur->next;
		}
	}
	return (lst);
}
