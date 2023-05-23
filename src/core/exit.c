/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:52:45 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/14 12:56:01 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	valid_number(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (*str == 0 || ft_templatecmp(&str[1], "-:+", ':'))
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	shell_exit(int c, char **v)
{
	if (c == 1)
		exit(g_shell.last_stts);
	else if (!valid_number(v[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(v[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		set_last_status(-1);
	}
	else if (c > 2)
	{
		msh_err("exit: too many arguments", NULL);
		set_last_status(1);
	}
	else
		set_last_status(ft_atoi(v[1]));
	exit(g_shell.last_stts);
	return (0);
}
