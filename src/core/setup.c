/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:21:05 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/14 15:38:27 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

/*
 *
 *	handle error properly when get_current_wd() returns NULL
 * 
 */

int	setup(char *env[])
{
	char	*path;

	g_shell.env = new_dictionary(env, '=');
	if (g_shell.env == NULL)
		return (1);
	g_shell.builtins = construct_builtins_list();
	if (g_shell.builtins == NULL)
		return (ft_lstclear(&g_shell.env, (t_lstdel)destroy_keyvalue), 1);
	g_shell.wd = getcwd(NULL, 0);
	if (g_shell.wd == NULL)
		return (1);
	path = get_env_var("PATH");
	if (path == NULL)
	{
		set_env_var("PATH","/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		path = get_env_var("PATH");
	}// if path is still NULL return (1);
	g_shell.paths = ft_split(path, ':');
	free(path);
	g_shell.last_stts = 0;
	return (0);
}
