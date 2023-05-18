/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:03:28 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 20:24:31 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	check_identifier(char *key)
{
	if (key == NULL)
		return (1);
	else if (!(ft_isalpha(*key) || *key == '_'))
		return (1);
	while (*(++key))
		if (!(ft_isalnum(*key) || *key == '_'))
			return (1);
	return (0);
}

void	msh_log(char *cmd, char *msg, char *arg, t_bool quotes)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		if (*arg && quotes == TRUE)
			ft_putchar_fd('`', 2);
		ft_putstr_fd(arg, 2);
		if (*arg && quotes == TRUE)
			ft_putchar_fd('\'', 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
}

void	msh_err(char *msg, char *token)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(msg, 2);
	if (token)
	{
		ft_putstr_fd(" ", 2);
		ft_putchar_fd('`', 2);
		ft_putstr_fd(token, 2);
		ft_putchar_fd('\'', 2);
	}
	ft_putstr_fd("\n", 2);
}

