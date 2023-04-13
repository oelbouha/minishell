/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_token_to_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:33:56 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/10 13:33:57 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	push_null_to_list(t_list **lst, char *token)
{
	t_list	*node;

	token = ft_strdup("NULL");
	if (token == NULL)
		return (1);
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		return (1);
	}
	ft_lstadd_back(lst, node);
	return (0);
}

int	push_token_to_list(t_list **lst, char *token)
{
	t_list	*node;

	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		return (1);
	}
	ft_lstadd_back(lst, node);
	if (check_unclosed_quotes(token))
	{
		if (push_null_to_list(lst, token))
			return (1);
	}
	return (0);
}