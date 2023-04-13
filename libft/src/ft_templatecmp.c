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
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (template[i])
	{
		if (ft_strncmp(str, &template[i], len) == 0)
			if (template[i + len] == delimiter || template[i + len] == 0)
				return (1);
		while (template[i] && template[i] != delimiter)
			i++;
		i++;
	}
	return (0);
}
