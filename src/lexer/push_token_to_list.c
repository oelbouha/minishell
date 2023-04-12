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

int	push_token_to_list(t_list **lst, char *token, int *err)
{
	t_list	*node;

	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		*err = 1;
		return (1);
	}
	ft_lstadd_back(lst, node);
	return (0);
}