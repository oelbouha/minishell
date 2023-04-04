/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:41:48 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/04 17:05:27 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	add_builtin(t_list **builtins, char *name, t_builtin *f)
{
	t_list		*node;
	t_keyvalue	*kv;
	char		*key;

	key = ft_strdup(name);
	if (key == NULL)
		return (1);
	kv = new_keyvalue(key, f);
	if (kv == NULL)
		return (free(key), 1);
	node = ft_lstnew(kv);
	if (node == NULL)
		return (destroy_keyvalue(kv), 1);
	ft_lstadd_back(builtins, node);
	return (0);
}

t_list	*construct_builtins_list(void)
{
	t_list	*builtins;

	builtins = NULL;
	if (add_builtin(&builtins, "cd", cd))
		return (NULL);
	if (add_builtin(&builtins, "echo", echo))
		return (ft_lstclear(&builtins, (t_lstdel)destroy_keyvalue), NULL);
	if (add_builtin(&builtins, "export", shell_export))
		return (ft_lstclear(&builtins, (t_lstdel)destroy_keyvalue), NULL);
	if (add_builtin(&builtins, "pwd", pwd))
		return (ft_lstclear(&builtins, (t_lstdel)destroy_keyvalue), NULL);
	if (add_builtin(&builtins, "env", env))
		return (ft_lstclear(&builtins, (t_lstdel)destroy_keyvalue), NULL);
	if (add_builtin(&builtins, "unset", unset))
		return (ft_lstclear(&builtins, (t_lstdel)destroy_keyvalue), NULL);
	return (builtins);
}
