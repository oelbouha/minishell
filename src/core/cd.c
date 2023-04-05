/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/05 18:17:00 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	cd(int c, char **v)
{
	char	*to;

	if (c == 1)
	{
		t_keyvalue *kv = get_env_var("HOME");
		to = (char *) kv->value;
	}
	else
		to = v[0];
	if (chdir(to))
		return (printf("Error: %s\n", strerror(errno)));
	free(g_shell.wd);
	g_shell.wd = getcwd(NULL, 0);
	if (g_shell.wd == NULL)
		return (1);//handle error properly
	return (0);
}
