/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setter_and_getter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/06 22:40:24 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

t_keyvalue	*get_env_var(char *key)
{
	return (find_in_dictionary(g_shell.env, key));
}

static char	*env_join(const char *key, const char *value)
{
	char	*k;
	char	*v;

	v = ft_strjoin(key, " ");
	if (v == NULL)
		return (NULL);
	k = ft_strjoin(v, value);
	free(v);
	if (k == NULL)
		return (NULL);
	k[ft_strlen(key)] = 0;
	return (k);
}

int	set_env_var(char *key, char *value)
{
	t_list		*node;
	t_keyvalue	*kv;
	char		*k;
	char		*v;

	kv = find_in_dictionary(g_shell.env, key);
	if (kv && value == NULL)
		return (0);
	v = NULL;
	if (kv == NULL && value == NULL)
		k = ft_strdup(key);
	else
	{
		k = env_join(key, value);
		if (k)
			v = &k[ft_strlen(key) + 1];
	}
	if (k == NULL)
		return (1);
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
