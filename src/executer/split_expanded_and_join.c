/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:07:55 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/11 22:08:01 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

t_list	*split_expanded(char *expanded)
{
	t_list	*new_lst;
	t_list	*node;
	char	**arr;
	int		i;

	new_lst = NULL;
	expanded = ft_replace(expanded, ' ');
	arr = ft_split(expanded, ' ');
	if (arr == NULL)
		return (free(expanded), NULL);
	free(expanded);
	i = -1;
	while (arr[++i])
	{
		node = ft_lstnew(arr[i]);
		if (node == NULL)
			return (ft_lstclear(&new_lst, free), free_arr(&arr[i]), NULL);
		ft_lstadd_back(&new_lst, node);
	}
	free(arr);
	return (new_lst);
}

int	join_prev_with_newlst(t_list **prv, t_list **lst, t_list **newlst)
{
	t_list		*last;
	char		*str;
	int			newlst_len;
	char		*content;

	last = ft_lstlast(*newlst);
	newlst_len = ft_lstsize(*newlst);
	str = (*prv)->content;
	content = ft_strjoin(str, (*newlst)->content);
	if (content == NULL)
		return (ft_lstdelone(*prv, free), -1);
	free(str);
	(*prv)->content = content;
	ft_lstdel_first(lst, free);
	last->next = *lst;
	ft_lstdel_first(newlst, free);
	(*prv)->next = *newlst;
	if (newlst_len > 1)
		*prv = last;
	return (0);
}

int	expand_and_join(t_list **prv, t_list **lst, t_list **tmp, char *expnded)
{
	t_list	*last;
	t_list	*newlst;

	newlst = split_expanded(expnded);
	if (newlst == NULL)
		return (ft_lstclear(lst, free), -1);
	last = ft_lstlast(newlst);
	if (*prv)
	{
		if (join_prev_with_newlst(prv, lst, &newlst) == -1)
			return (ft_lstclear(&newlst, free), ft_lstclear(lst, free), -1);
	}
	else
	{
		*prv = newlst;
		last->next = (*lst)->next;
		ft_lstdel_first(lst, free);
		*lst = last->next;
		*tmp = *prv;
		*prv = last;
	}
	return (0);
}

void	not_a_valid_var(t_list **lst, t_list **prev, char *expanded)
{
	ft_lstdel_first(lst, free);
	free(expanded);
	if (*prev)
		(*prev)->next = *lst;
}

t_list	*split_and_join(t_list *lst)
{
	t_list	*new_lst;
	t_list	*prev;
	char	*expanded;

	if (lst == NULL)
		return (NULL);
	prev = NULL;
	new_lst = EMPTY_LST;
	while (lst)
	{
		if (needs_spliting(lst->content))
		{
			expanded = expand_var(lst->content);
			if (*expanded == 0)
				not_a_valid_var(&lst, &prev, expanded);
			else if (expand_and_join(&prev, &lst, &new_lst, expanded) == -1)
				return (NULL);
		}
		else if (remove_quotes_and_expand(&prev, &lst, &new_lst) == -1)
			return (NULL);
	}
	return (new_lst);
}
