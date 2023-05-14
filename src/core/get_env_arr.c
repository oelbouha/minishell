/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:46:03 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/14 16:00:18 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

char	**get_env_arr(void)
{
	char		**env_arr;
	t_list		*env;
	t_keyvalue	*kv;
	int			size;
	int			i;

	size = ft_lstsize(g_shell.env);
	env_arr = ft_calloc(size + 1, sizeof(char *));
	if (env_arr == NULL)
		return (NULL);
	env = g_shell.env;
	i = -1;
	while (++i < size)
	{
		kv = env->content;
		kv->key[ft_strlen(kv->key)] = '=';
		env_arr[i] = kv->key;
		env = env->next;
	}
	return (env_arr);
}
