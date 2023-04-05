/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:21:05 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/05 22:09:36 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	setup(char *env[])
{
	ft_bzero(&g_shell, sizeof(t_shell));
	g_shell.env = new_dictionary(env, '=');
	if (g_shell.env == NULL)
		return (1);
	g_shell.builtins = construct_builtins_list();
	if (g_shell.builtins == NULL)
		return (ft_lstclear(&g_shell.env, (t_lstdel)destroy_keyvalue), 1);
	g_shell.wd = get_current_wd();
	if (g_shell.wd == NULL)
		return (1);//handle error properlly
	g_shell.last_stts = 0;
	return (0);
}
