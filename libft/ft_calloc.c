/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:24:07 by oelbouha          #+#    #+#             */
/*   Updated: 2022/10/06 18:41:08 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t items, size_t size)
{
	char		*ptr;
	size_t		i;

	ptr = malloc (items * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (items * size))
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}
