/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:56:55 by ysalmi            #+#    #+#             */
/*   Updated: 2023/03/24 12:36:27 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_internal.h"
typedef void (*lstdel)(void *);


t_list	*make_env_list(char **env_arr)
{
	t_list		*env;
	t_keyvalue	*kv;
	char		*key;
	char		*value;
	int			i;

	env = NULL;
	i = -1;
	while (env_arr && env_arr[++i])
	{
		key = ft_strdup(env_arr[i]);
		if (key == NULL)
			return (ft_lstclear(&env, (lstdel)destroy_keyvalue), NULL);
		value = ft_strchr(key, '=');
		key[value++ - key] = 0;
		kv = new_keyvalue(key, value);
		if (kv == NULL)
			return (ft_lstclear(&env, (lstdel)destroy_keyvalue), free(key), NULL);
		ft_lstadd_back(&env, ft_lstnew(kv));
	}
	return (env);
}
