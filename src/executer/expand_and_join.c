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

char	*duplicate_or_expand(char *content)
{
	char	*expanded;

	if (should_expand_var(content))
	{
		expanded = expand_var(content);
		if (expanded == NULL)
			return (NULL);
	}
	else
		expanded = ft_strdup(content);
	return (expanded);
}

char	*join_expanded(char *expanded, char *content)
{
	char	*str;

	str = NULL;
	if (*content != 0)
	{
		if (expanded != EMPTY_VAR)
			str = expanded;
		content = remove_quotes(content);
		expanded = ft_strjoin(str, content);
		if (expanded == NULL)
			return (NULL);
		free(str);
	}
	free(content);
	return (expanded);
}

char	*expand_and_join(t_list *lst)
{
	t_list	*cur;
	char	*expanded;
	char	*content;

	cur = lst;
	expanded = EMPTY_VAR;
	while (cur)
	{
		if (needs_spliting(cur->content))
		{
			content = expand_var(cur->content);
			ft_replace(content, 30);
		}
		else
			content = duplicate_or_expand(cur->content);
		if (content == NULL)
			return (ft_lstclear(&lst, free), NULL);
		expanded = join_expanded(expanded, content);
		if (expanded == NULL)
			return (ft_lstclear(&lst, free), NULL);
		cur = cur->next;
	}
	return (ft_lstclear(&lst, free), expanded);
}
