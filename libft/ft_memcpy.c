/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:45:57 by oelbouha          #+#    #+#             */
/*   Updated: 2022/10/06 19:45:37 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	char	*source;

	if (dst == 0 && src == 0)
		return (0);
	dest = (char *)dst;
	source = (char *)src;
	while (n > 0)
	{
		*dest = *source;
		dest++;
		source++;
		n--;
	}
	return (dst);
}
