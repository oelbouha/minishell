/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:18:36 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/12 11:18:37 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace(char *str, char c)
{
	char	*temp;
	int		i;

	temp = str;
	i = 0;
	while (*temp && (*temp == ' ' || *temp == '\t'))
		temp++;
	while (*temp)
	{
		if (*temp == ' ' || *temp == '\t')
		{
			while (*temp && (*temp == ' ' || *temp == '\t'))
				temp++;
			if (*temp == 0)
				break ;
			str[i++] = c;
		}
		else
		{
			str[i++] = *temp;
			temp++;
		}
	}
	str[i] = '\0';
	return (str);
}
