/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/07 17:28:22 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	get_env_var_len(char *key)
{
	t_keyvalue	*kv;

	if (ft_strcmp(key, "$") == 0)
		return (0);
	else if (ft_strcmp(key, "?") == 0)
		return (3);
	kv = find_in_dictionary(g_shell.env, key);
	if (kv == NULL)
		return (0);
	return (ft_strlen((char *)kv->value));
}

char	*get_env_var(char *key)
{
	t_keyvalue	*kv;

	if (ft_strcmp(key, "$") == 0)
		return (NULL);
	else if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(get_last_status()));
	kv = find_in_dictionary(g_shell.env, key);
	if (kv == NULL)
		return (NULL);
	return (ft_strdup((char *)kv->value));
}
