/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/14 14:17:28 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	pwd(int c, char **v)
{
	char	*wd;

	(void)c;
	(void)v;
	wd = get_current_wd();
	if (wd == NULL)
		return (1);
	ft_putstr_fd(wd, 1);
	ft_putstr_fd("\n", 1);
	free(wd);
	return (0);
}
