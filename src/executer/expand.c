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

t_list	*split_expanded(char *expanded)
{
	t_list	*newlst;
	t_list	*node;
	char 	**arr;
	int		i;

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
		return ((t_list *)EMPTY_VAR);
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

void add_nodes_to_lst(t_list *temp, t_list **lst)
{
	t_list	*last;

	if (temp == (t_list *)EMPTY_VAR)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = temp;
	}
	else
		*lst = temp;
}

int	get_new_node(char *content, t_list **lst)
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
	ft_lstadd_back(lst, node);
	return (0);
}

t_list	*expand(t_list *lst)
{
	t_list	*expanded_lst;
	t_list	*temp;
	t_list	*cur;

	cur = lst;
	temp = NULL;
	expanded_lst = NULL;
	while (cur)
	{
		if (should_expand_wildcard(cur->content))
		{
			temp = expand_wildcard(cur->content);
			if (temp == NULL)
				return (ft_lstclear(&expanded_lst, free), NULL);
			add_nodes_to_lst(temp, &expanded_lst);
		}
		else if (should_expand(cur->content))
		{
			temp = get_expanded(cur->content);
			if (temp == NULL)
				return (ft_lstclear(&expanded_lst, free), NULL);
			add_nodes_to_lst(temp, &expanded_lst);
		}
		else
		{
			if (get_new_node(cur->content, &expanded_lst))
				return(ft_lstclear(&expanded_lst, free), NULL);
		}
		cur = cur->next;
	}
	return (expanded_lst);
}
