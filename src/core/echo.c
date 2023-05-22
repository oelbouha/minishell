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

int check_args(char **v)
{
	int i;

	i = 1;
	while (v[i])
	{
		if (ft_strcmp(v[i], "-n") == 0)
			i++;
		else if (v[i][0] == '-' && ft_issubset("n", &v[i][1]))
			i++;
		else			
			break ;	
	}
	return (i);
}

int	echo(int c, char **v)
{
	int		nl;
	int		i;

	nl = 1;
	if (c > 1)
	{
		if (v[1][0] == '-' && ft_issubset("n", &v[1][1]))
			nl = 0;
		i = check_args(v);
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
