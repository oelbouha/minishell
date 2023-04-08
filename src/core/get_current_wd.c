/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_wd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:11:29 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/07 17:35:41 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

char	*get_current_wd(void)
{
	if (g_shell.wd)
		return (ft_strdup(g_shell.wd));
	g_shell.wd = getcwd(NULL, 1024);
	return (ft_strdup(g_shell.wd));
}
