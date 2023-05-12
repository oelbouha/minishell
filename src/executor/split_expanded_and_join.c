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

#include "../parser/parser.h"

t_list	*split_var(char *expanded)
{
	t_list	*new_lst;
	t_list	*node;
	char	**arr;

	new_lst = NULL;
	arr = ft_split(expanded, ' ');
	free(expanded);
	if (arr == NULL)
		return (NULL);
	int i = -1;
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
	t_list	*last;
	char	*str;
	char	*content;

	last = ft_lstlast(*newlst);
	print(*newlst);
	str = (*prv)->content;
	printf("prev content : %s\n", str);
	content = ft_strjoin(str, (*newlst)->content);
	if (content == NULL)
		return (-1);
	printf("after join : %s\n", content);
	free(str);
	(*prv)->content = content;
	// ft_lstdel_first(lst, free);
	last->next = (*lst)->next;
	// ft_lstdel_first(newlst, free);
	(*prv)->next = (*newlst)->next;
	*lst = last->next;
	*prv = last;
	printf("after join : %s\n", content);
	return (0);
}

int	expand_var_ad_join(t_list **prv, t_list **lst, t_list **tmp, char *expnded)
{
	t_list	*last;
	t_list	*newlst;

	newlst = split_var(expnded);
	if (newlst == NULL)
		return (-1);
	last = ft_lstlast(newlst);
	if (*prv)
	{
		if (join_prev_with_newlst(prv, lst, &newlst) == -1)
			return (ft_lstclear(&newlst, free), -1);
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

	prev = NULL;
	new_lst = EMPTY_LST;
	while (lst)
	{
		if (needs_spliting(lst->content))
		{
			expanded = expand_var(lst->content);
			if (*expanded == 0)
				not_a_valid_var(&lst, &prev, expanded);
			else if(expand_var_ad_join(&prev,  &lst, &new_lst, expanded) == -1)
				return (ft_lstclear(&new_lst, free), NULL);
		}
		else if(remove_quotes_and_expand(&prev, &lst, &new_lst) == -1)
			return (NULL);
	}
	return (new_lst);
}
