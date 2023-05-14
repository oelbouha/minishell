/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:00:58 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/14 12:15:21 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

t_builtin	get_builtin(char *key)
{
	t_keyvalue	*kv;

	kv = find_in_dictionary(g_shell.builtins, key);
	if (kv == NULL)
		return (NULL);
	return ((t_builtin)kv->value);
}
