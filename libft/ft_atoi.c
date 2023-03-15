/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:39:02 by oelbouha          #+#    #+#             */
/*   Updated: 2022/10/06 18:36:50 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h" 

int	ft_atoi(char *str)
{
	unsigned int	res;
	int				sign;
	int				i;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\t')
		i++;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - 48;
		i++;
	}
	res *= sign;
	return (res);
}
