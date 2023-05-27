/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:07:46 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/27 14:23:56 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

t_list	*split_expanded(char *expanded)
{
	t_list		*newlst;
	t_list		*node;
	char		**arr;
	int			i;

	newlst = NULL;
	arr = ft_split(expanded, 30);
	free(expanded);
	if (arr == NULL)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		node = ft_lstnew(arr[i]);
		if (node == NULL)
			return (free_arr(&arr[i]), ft_lstclear(&newlst, free), NULL);
		ft_lstadd_back(&newlst, node);
	}
	free(arr);
	if (newlst == NULL)
		return (EMPTY_LST);
	return (newlst);
}

t_list	*get_expanded(char *content)
{
	char		*expanded;
	t_list		*temp;
	t_list		*node;
	t_list		*lst;

	temp = NULL;
	lst = split_content(content);
	if (lst == NULL)
		return (NULL);
	expanded = expand_and_join(lst);
	if (expanded == NULL)
		return (NULL);
	else if (expanded == EMPTY_VAR)
		return ((t_list *)EMPTY_VAR);
	else if (ft_strchr(expanded, 30))
		return (split_expanded(expanded));
	node = ft_lstnew(expanded);
	if (node == NULL)
		return (NULL);
	ft_lstadd_back(&temp, node);
	return (temp);
}

void	add_newlst_to_expanded_lst(t_list *newlst, t_list **lst)
{
	t_list	*last;

	if (newlst == EMPTY_LST)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = newlst;
	}
	else
		*lst = newlst;
}

int	duplicate_and_remove_quotes(char *content, t_list **expanded)
{
	char	*str;
	t_list	*node;

	str = ft_strdup(content);
	if (str == NULL)
		return (1);
	str = remove_quotes(str);
	node = ft_lstnew(str);
	if (node == NULL)
		return (free(str), 1);
	ft_lstadd_back(expanded, node);
	return (0);
}

t_list	*expand(t_list *lst)
{
	t_list	*expanded_lst;
	t_list	*newlst;
	t_list	*cur;

	cur = lst;
	newlst = EMPTY_LST;
	expanded_lst = NULL;
	while (cur)
	{
		if (should_expand_var(cur->content))
		{
			newlst = get_expanded(cur->content);
			if (newlst == NULL)
				return (ft_lstclear(&expanded_lst, free), NULL);
			add_newlst_to_expanded_lst(newlst, &expanded_lst);
		}
		else if (duplicate_and_remove_quotes(cur->content, &expanded_lst))
			return (ft_lstclear(&expanded_lst, free), NULL);
		cur = cur->next;
	}
	if (expanded_lst == NULL)
		return (EMPTY_LST);
	return (expanded_lst);
}
