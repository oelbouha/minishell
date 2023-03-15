/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:47:28 by oelbouha          #+#    #+#             */
/*   Updated: 2022/10/03 18:41:28 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*fresh;
	int		i;
	int		j;

	i = ft_strlen(s1) + 1;
	fresh = malloc(sizeof(char) * i);
	if (!fresh)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i])
	{
		fresh[j] = s1[i];
		i++;
		j++;
	}
	fresh[j] = '\0';
	return (fresh);
}
