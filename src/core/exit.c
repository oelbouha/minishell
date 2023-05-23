/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:52:45 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/23 16:26:34 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	valid_number(char *str)
{
	if (ft_templatecmp(&str[1], "-:+", ':'))
		return (0);
	if (*str == '+' || *str == '-')
		str++;
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
	if (c == 2 && !valid_number(v[1]))
	{
		msh_err("exit: numeric argument required", v[1]);
		set_last_status(-1);
	}
	else if (c > 2)
	{
		msh_err("exit: too many arguments", NULL);
		set_last_status(1);
	}
	else if (c == 2)
		set_last_status(ft_atoi(v[1]));
	destroy();
	exit(g_shell.last_stts);
	return (0);
}
