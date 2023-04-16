/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/16 17:46:50 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

static void	print_exports(void)
{
	t_list		*cur;
	t_keyvalue	*kv;
	char		*value;

	cur = g_shell.env;
	while (cur)
	{
		kv = (t_keyvalue *)cur->content;
		value = (char *)kv->value;
		printf("declare -x %s", kv->key);
		if (value)
			printf("=\"%s\"", value);
		printf("\n");
		cur = cur->next;
	}
}

int	shell_export(int c, char **v)
{
	char	*key;
	char	*value;
	int		err;
	int		i;

	if (c == 1)
		return (print_exports(), 0);
	err = 0;
	i = 0;
	while (++i < c)
	{
		key = ft_strdup(v[i]);
		if (key == NULL)
			return (1);
		value = ft_strchr(key, '=');
		if (value)
			key[value++ - key] = 0;
		if (check_identifier(key) && ++err)
			msh_log("export", "not a valid identifier", v[i], TRUE);
		else if (set_env_var(key, value))
			return (free(key), 1);
		else if (ft_strcmp(key, "PATH") == 0)
		{
			//free_string_arr(g_shell.path);
			g_shell.path = ft_split(value, ':');
		}
		free(key);
	}
	return (err > 0);
}
