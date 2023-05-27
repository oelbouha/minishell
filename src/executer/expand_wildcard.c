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

int	needs_wildcard_expansion(char *line)
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
	t_list	*matches;

	cur = lst;
	newlst = (t_list *)-1;
	matches = NULL;
	while (cur)
	{
		if (needs_wildcard_expansion(cur->content))
		{
			newlst = expand_wildcard_character(cur->content);
			if (newlst == NULL)
				return (ft_lstclear(&matches, free), NULL);
			add_newlst_to_expanded_lst(newlst, &matches);
		}
		else if (duplicate_and_remove_quotes(cur->content, &matches))
			return (ft_lstclear(&matches, free), NULL);
		cur = cur->next;
	}
	return (matches);
}
