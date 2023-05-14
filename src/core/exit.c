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

int	shell_exit(int c, char **v)
{
	(void)c;
	(void)v;
	exit(g_shell.last_stts);
	return (0);
}