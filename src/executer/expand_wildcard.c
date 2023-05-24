/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcaard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:07:44 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/22 16:07:46 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	should_expand(char *line)
{
	int	ret;

	ret = 0;
	while (*line)
	{
		if (*line == '$' || *line == '"' || *line == '\'')
			return (0);
		else if (*line == '*')
			ret = 1;
		line++;
	}
	return (ret);
}

t_list	*expand_wildcard(t_list *lst)
{
	t_list	*cur;
	t_list	*newlst;
	t_list	*expanded;

	cur = lst;
	newlst = EMPTY_LST;
	expanded = NULL;
	while (cur)
	{
		if (should_expand(cur->content))
		{
			newlst = wildcard(cur->content);
			if (newlst == NULL)
				return (ft_lstclear(&expanded, free), NULL);
			add_nodes_to_lst(newlst, &expanded);
		}
		else if (get_new_node(cur->content, &expanded))
			return (ft_lstclear(&expanded, free), NULL);
		cur = cur->next;
	}
	return (expanded);
}
