/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_args_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:22:29 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/23 20:34:58 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_bonus.h"

int	should_expand(t_list *lst)
{
	t_list	*cur;

	cur = lst;
	while (cur)
	{
		if (should_expand_wildcard(cur->content))
			return (1);
		cur = cur->next;
	}
	return (0);
}

char	**prep_args(t_list *args_lst)
{
	char	**arr;
	t_list	*args;
	t_list	*lst;

	lst = expand(args_lst);
	if (lst == NULL)
		return (NULL);
	if (should_expand(lst))
	{
		args = expand_wildcard(lst);
		if (args == NULL)
			return (ft_lstclear(&lst, free), NULL);
		ft_lstclear(&lst, free);
		arr = ft_lst_to_arr(args);
		ft_lstclear(&args, do_nothing);
	}
	else
	{
		arr = ft_lst_to_arr(lst);
		ft_lstclear(&lst, do_nothing);
	}
	if (arr == NULL)
		return (ft_lstclear(&args, free), NULL);
	return (arr);
}
