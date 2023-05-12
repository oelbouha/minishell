/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_and_expand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:08:28 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/11 22:08:31 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

char	*remove_quotes_and_expand_var(char *content)
{
	char	*expanded;
	char	*str;

	if (should_expand_var(content))
	{
		expanded = remove_quotes(content);
		str = content;
		expanded = expand_var(str);
		if (expanded == NULL)
			return (free(str), NULL);
		free(str);
	}
	else
		expanded = remove_quotes(content);
	return (expanded);
}

int	remove_quotes_and_expand(t_list **prev, t_list **lst, t_list **new_lst)
{
	char	*str;
	char	*content;

	str = remove_quotes_and_expand_var((*lst)->content);
	if (str == NULL)
		return (ft_lstclear(lst, free), -1);
	(*lst)->content = str;
	
	if (*prev)
	{
		// print(*new_lst);
		str = (*prev)->content;
		content = ft_strjoin(str, (*lst)->content);
		if (content == NULL)
			return (ft_lstclear(new_lst, free), -1);
		(*prev)->content = content;
		// free(str);
		// ft_lstdel_first(lst, free);
		(*prev)->next = (*lst)->next;
		*lst = (*prev)->next;
	}
	else
	{
		*prev = *lst;
		*lst = (*lst)->next;
		*new_lst = *prev;
	}
	return (0);
}
