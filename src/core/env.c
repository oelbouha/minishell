/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/04 17:52:13 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	env(int c, char **v)
{
	(void)c;
	(void)v;
	printf("builtin: env\n");
	return (0);
}

t_keyvalue	*get_env_var(char *key)
{
	return (find_in_dictionary(g_shell.env, key));
}

int	set_env_var(char *key, char *value)
{
	t_list		*node;
	t_keyvalue	*kv;
	char		*k;
	char		*v;

	if (value == NULL)
		value = "";
	v = ft_strjoin(key, " ");
	if (v == NULL)
		return (1);
	k = ft_strjoin(v, value);
	free(v);
	if (k == NULL)
		return (1);
	kv = find_in_dictionary(g_shell.env, key);
	k[ft_strlen(key)] = 0;
	if (kv)
	{
		free(kv->key);
		kv->key = k;
		kv->value = &k[ft_strlen(key) + 1];
		return (0);
	}
	kv = new_keyvalue(k, &k[ft_strlen(key) + 1]);
	if (kv == NULL)
		return (free(k), 1);
	node = ft_lstnew(kv);
	if (node == NULL)
		return (destroy_keyvalue(kv), 1);
	ft_lstadd_back(&g_shell.env, node);
	return (0);
}
