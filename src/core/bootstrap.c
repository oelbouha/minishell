/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bootstrap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:21:05 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/04 17:54:07 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	set_up(char *env[])
{
	g_shell.env = new_dictionary(env, '=');
	if (g_shell.env == NULL)
		return (1);
	g_shell.builtins = construct_builtins_list();
	if (g_shell.builtins == NULL)
		return (ft_lstclear(&g_shell.env, (t_lstdel)destroy_keyvalue), 1);
	g_shell.last_stts = 0;
	return (0);
}

int	main(int c, char **v, char **e)
{
	printf("bootstraping... [%d]\n", set_up(e));
	set_env_var("name", NULL);
	t_keyvalue	*kv = get_env_var("name");
	printf("%s => %s\n", kv->key, (char *)kv->value);
	t_list *cur = g_shell.env;
	printf("env:\n");
	while (cur)
	{
		t_keyvalue *kv = cur->content;
		printf("\t%s=%s\n",kv->key, kv->value);
		cur = cur->next;
	}
	cur = g_shell.builtins;
	printf("builtins:\n");
	int	i = 0;
	while (cur)
	{
		printf("\t");
		t_keyvalue *kv = cur->content;
		t_builtin *builtin = kv->value;
		(*builtin)(0, NULL);
		cur = cur->next;
	}
	return (0);
}
