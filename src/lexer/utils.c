/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:31:10 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/11 18:11:13 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print(t_list *lst)
{
	t_list	*temp;
	int		i;

	temp = lst;
	if (!temp)
		return ;
	i = 1;
	while (temp)
	{
		printf("[%2d]: %s\n", i++, temp->content);
		temp = temp->next;
	}
}
