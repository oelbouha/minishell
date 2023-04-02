/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bootstrap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:21:05 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/02 12:33:02 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	bootstrap(char *env[])
{
	shell.env = new_dictionary(env, '=');
	if (shell.env == NULL)
		return (1);
	shell.builtins = construct_builtins_list();
	if (shell.builtins == NULL)
		return (ft_lstclear(&shell.env, (t_lstdel)destroy_keyvalue), 1);
	shell.last_stts = 0;
}
