/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/06 23:12:33 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	env(int c, char **v)
{
	t_list		*cur;
	t_keyvalue	*kv;

	(void)c;
	(void)v;
	if (c > 1)
		return (msh_log("env", "Command arguments are NOT supported\n", ""), 1);
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
