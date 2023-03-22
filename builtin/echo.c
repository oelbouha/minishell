/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:33:29 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/21 19:33:45 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **args)
{
	int		i;
	int		check;

	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		i = 1;
		check = 0;
	}
	else
	{
		i = 0;
		check = 1;
	}
	if (args[i + 1])
	{
		while (args[++i])
			ft_putstr_fd(args[i], 1);
	}
	if (check)
		ft_putstr_fd("\n", 1);
}