/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/06 11:00:53 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	env(int c, char **v)
{
	t_list		*cur;
	t_keyvalue	*kv;
	char		*value;

	(void)c;
	(void)v;
	if (c > 1)
		ft_putstr_fd("Minishell: env: command args are not supported\n", 2);
	cur = g_shell.env;
	while (cur)
	{
		kv = (t_keyvalue *) cur->content;
		value = (char *) kv->value;
		if (value && *value)
		{
			ft_putstr_fd(kv->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(kv->value, 1);
			ft_putchar_fd('\n', 1);
		}
		cur = cur->next;
	}
	return (0);
}
