/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:31:10 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/09 15:26:50 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	cant_be_last(char *token)
{
	return (ft_templatecmp(token, "<<:>>:>:|:<", ':')
		|| (BONUS && ft_templatecmp(token, "||:&&:(", ':')));
}

int		is_operator(char c, char s)
{
	if (ft_strchr(" ><|\t", c))
		return (1);
	else if (BONUS && ((c == ')' || c == '(') || (c == '&' && s == '&')))
		return (1);
	return (0);
}

int	word_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(" ><|\t\"'", str[i]))
			return (i);
		else if (BONUS && (str[i] == ')' || str[i] == '('
			|| !ft_strncmp(&str[i], "&&", 2)))
			return (i);
		i++;
	}
	return (i);
}

t_list	*remove_last_node(t_list **lst)
{
	t_list	*cur;

	if (lst == NULL)
		return (NULL);
	cur = *lst;
	if (cur->next == NULL)
	{
		free(cur->content);
		free(cur);
		*lst = NULL;
		return (NULL);
	}
	while (cur->next->next)
		cur = cur->next;
	free(cur->next->content);
	free(cur->next);
	cur->next = NULL;
	return (cur);
}
