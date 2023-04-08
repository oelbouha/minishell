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

char	*get_env_var(char *key)
{
	t_keyvalue	*kv;

	kv = find_in_dictionary(g_shell.env, key);
	if (kv == NULL)
		return (NULL);
	return (ft_strdup((char *)kv->value));
}
