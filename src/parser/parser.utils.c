/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:41:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/12 10:42:16 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_ann_operator(const char *token)
{
	int	ret;

	ret = (ft_templatecmp(token, "|:>:>>:<:<<", ':')
			|| (BONUS && ft_templatecmp(token, "(:):||:&&", ':')));
	return (ret);
}

int	is_redirection(const char *token)
{
	return (ft_templatecmp(token, ">:>>:<:<<", ':'));
}

//move node moves a node from a linked list to another and
//returns the node next to the node moved.
t_list	*move_node(t_list **to, t_list *node, t_list *prev)
{
	t_list	*temp;

	if (prev)
		prev->next = node->next;
	else
		temp = node->next;
	node->next = NULL;
	ft_lstadd_back(to, node);
	if (prev)
		return (prev->next);
	return (temp);
}
