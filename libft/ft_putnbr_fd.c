/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:06:25 by oelbouha          #+#    #+#             */
/*   Updated: 2022/10/04 10:07:31 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	i;
	unsigned int	n;
	int				sign;
	char			str[12];

	sign = -1;
	if (nb < 0)
	{
		write(fd, "-", 1);
		n = nb * sign;
	}
	else
		n = nb;
	i = 10;
	while (n / 10)
	{
		str[i] = n % 10 + 48;
		n = n / 10;
	i--;
	}
	str[i] = n % 10 + 48;
	write (fd, &str[i], 11 - i);
}
