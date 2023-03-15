/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:52:18 by oelbouha          #+#    #+#             */
/*   Updated: 2022/10/14 18:27:45 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		dest_len;

	if (size == 0)
		return (ft_strlen(src));
	dest_len = ft_strlen(dest);
	i = ft_strlen(dest);
	j = 0;
	if (dest_len > size)
		return (ft_strlen(src) + size);
	while (src[j] && i < size -1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest_len + ft_strlen(src));
}
