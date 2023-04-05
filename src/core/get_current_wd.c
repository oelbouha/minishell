/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_wd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:11:29 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/05 17:55:49 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

char	*get_current_wd(void)
{
	char	*ret;

	if (g_shell.wd)
		return (g_shell.wd);
	ret = getcwd(NULL, 1024);
	return (ret);
}
