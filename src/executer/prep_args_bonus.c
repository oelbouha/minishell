/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_args_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:22:29 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/23 22:12:57 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_bonus.h"

int	should_expand_wildcard(t_list *lst)
{
	t_list	*cur;

	cur = lst;
	while (cur)
	{
		if (should_expand(cur->content))
			return (1);
		cur = cur->next;
	}
	return (0);
}

char	**prep_args(t_list *args_lst)
{
	char	**arr;
	t_list	*args;
	t_list	*expanded;

	expanded = expand(args_lst);
	if (expanded == NULL)
		return (NULL);
	if (should_expand_wildcard(expanded))
	{
		args = expand_wildcard(expanded);
		if (args == NULL)
			return (ft_lstclear(&expanded, free), NULL);
		ft_lstclear(&expanded, free);
		arr = ft_lst_to_arr(args);
		ft_lstclear(&args, do_nothing);
	}
	else
	{
		arr = ft_lst_to_arr(expanded);
		ft_lstclear(&expanded, do_nothing);
	}
	if (arr == NULL)
		return (ft_lstclear(&args, free), NULL);
	return (arr);
}
