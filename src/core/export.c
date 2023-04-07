/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/07 14:36:57 by ysalmi           ###   ########.fr       */
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
	int		i;
	int		ret;

	if (c == 1)
		return (print_exports(), 0);
	ret = 0;
	i = 0;
	while (++i < c)
	{
		key = ft_strdup(v[i]);
		if (key == NULL)
			return (1);
		value = ft_strchr(key, '=');
		if (value)
			key[value++ - key] = 0;
		if (check_identifier(key) && ++ret)
			msh_log("export", "not a valid identifier", key, TRUE);
		else if (set_env_var(key, value))
			return (free(key), 1);
		free(key);
	}
	return (ret > 0);
}
