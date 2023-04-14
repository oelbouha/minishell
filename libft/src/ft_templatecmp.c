/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_templatecmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:16:17 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/13 13:55:51 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_templatecmp(char *str, char *template, char delimiter)
{
	int		i;
	char	**arr;

	arr = ft_split(template, delimiter);
	i = -1;
	while (arr[++i])
	{
		if (ft_strcmp(str, arr[i]) == 0)
			return (ft_free(arr), 1);
	}
	return (ft_free(arr), 0);
}

