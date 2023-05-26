/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/07 14:23:12 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	env(int c, char **v)
{
	t_list		*cur;
	t_keyvalue	*kv;

	(void)v;
	if (c > 1)
		return (msh_log("env", "command args are NOT supported", "", FALSE),
			1);
	cur = g_shell.env;
	while (cur)
	{
		kv = (t_keyvalue *) cur->content;
		if (kv->value)
			ft_printf("%s=%s\n", kv->key, (char *)kv->value);
		cur = cur->next;
	}
	return (0);
}
