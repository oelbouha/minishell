/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/22 21:38:48 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	remove_env_var(char *key)
{
	t_list		*cur;
	t_list		*prev;
	t_keyvalue	*kv;

	cur = g_shell.env;
	prev = NULL;
	while (cur)
	{
		kv = cur->content;
		if (ft_strcmp(key, kv->key) == 0)
			break ;
		prev = cur;
		cur = cur->next;
	}
	if (cur)
	{
		if (prev == NULL)
			g_shell.env = cur->next;
		else
			prev->next = cur->next;
		ft_lstdelone(cur, (t_lstdel)destroy_keyvalue);
	}
	return (1);
}

int	unset(int c, char **v)
{
	char	*key;
	int		i;
	int		ret;

	ret = 0;
	if (c > 1)
	{
		i = 0;
		while (++i < c)
		{
			key = v[i];
			if (check_identifier(key) && ++ret)
			{
				printf("minishell: unset: `%s\': not a valid identifier\n", key);
				continue ;
			}
			remove_env_var(key);
			if (ft_strcmp(key,"PATH"))
			{
				free_arr(g_shell.paths);
				g_shell.paths = NULL;
			}
		}
	}
	return (ret);
}
