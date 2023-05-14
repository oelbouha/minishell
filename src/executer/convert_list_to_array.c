/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:47:31 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/12 10:48:31 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

char	**convert_list_to_array(t_list	*lst)
{
	t_list	*temp;
	char	**arr;
	int		len;
	int		i;

	if (!lst)
		return (NULL);
	len = ft_lstsize(lst) + 1;
	arr = malloc(len * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (lst)
	{
		temp = lst;
		arr[i] = lst->content;
		lst = lst->next;
		free(temp);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
