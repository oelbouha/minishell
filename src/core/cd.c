/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/07 17:35:05 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	cd(int c, char **v)
{
	char		*to;

	if (c == 1)
	{
		to = get_env_var("HOME");
		if (chdir(to))
			return (free(to), msh_log("cd", strerror(errno), "", FALSE), 1);
		free(to);
	}
	else
	{
		to = v[0];
		if (chdir(to))
			return (msh_log("cd", strerror(errno), "", FALSE), 1);
	}
	free(g_shell.wd);
	g_shell.wd = getcwd(NULL, 0);
	if (g_shell.wd == NULL)
		return (msh_log("cd", strerror(errno), "", FALSE), 1);
	return (0);
}
