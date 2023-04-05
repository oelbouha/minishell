/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/05 22:10:29 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	echo(int c, char **v)
{
	int		nl;
	char	*arg;
	int		i;

	nl = 1;
	if (c > 1)
	{
		i = 1;
		arg = v[1];
		if (arg[0] == '-' && arg[1] == 'n' && arg[2] == 0)
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
		write(1, "\n", 1);
	return (0);
}
