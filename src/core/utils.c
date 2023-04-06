/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:03:28 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/06 23:28:26 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	check_identifier(char *key)
{

	if (key == NULL)
		return (1);
	else if (!(ft_isalpha(*key) || *key == '_'))
		return (printf("first\n"), 1);
	while (*(++key))
		if (!(ft_isalnum(*key) || *key == '_'))
			return (1);
	return (0);
}

void	msh_log(char *cmd, char *msg, char *arg)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	if (arg)
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
}
