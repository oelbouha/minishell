/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/20 12:02:46 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	echo(int c, char **v)
{
	int		nl;
	int		i;

	nl = 1;
	if (c > 1)
	{
		i = 1;
		if (v[1][0] == '-' && ft_issubset("n", &v[1][1]))
			nl -= i++;
		while (i < c)
		{
			ft_putstr_fd(v[i], 1);
			if (i != c - 1)
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
