/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/07 15:48:50 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

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
		v = k + ft_strlen(key) + 1;
	}
	if (k == NULL)
		return (1);
	if (kv)
		return (update_keyvalue(kv, k, v), 0);
	if (add_word_to_dictionary(&g_shell.env, k, v))
		return (free(k), 1);
	return (0);
}
