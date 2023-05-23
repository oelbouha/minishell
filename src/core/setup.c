/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:21:05 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/23 16:20:03 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

void	sig_int_handler(int signo)
{
	if (signo == SIGINT)
	{
		set_last_status(1);
		if (get_state() == 0)
		{
			ft_printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (get_state() == 1)
			ft_printf("\n");
		else if (get_state() == 2)
			set_state(1);
	}
}

int	update_env(void)
{
	char	*val;
	int		res;

	val = get_env_var("PATH");
	if (val == NULL)
		set_env_var("PATH","/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	free(val);
	val = get_env_var("SHLVL");
	if (val)
	{
		res = ft_atoi(val) + 1;
		free(val);
		val = ft_itoa(res);
		if (val == NULL)
			return (1);
		set_env_var("SHLVL", val);
		free(val);
	}
	return (0);
}


int	setup(char *env[])
{
	char	*path;

	g_shell.env = new_dictionary(env, '=');
	if (g_shell.env == NULL)
		return (1);
	g_shell.builtins = construct_builtins_list();
	if (g_shell.builtins == NULL)
		return (1);
	g_shell.wd = getcwd(NULL, 0);
	if (g_shell.wd == NULL)
		return (1);
	path = get_env_var("PATH");
	g_shell.paths = ft_split(path, ':');
	free(path);
	signal(SIGINT, sig_int_handler);
	if (update_env())
		return (1);
	return (0);
}

void	destroy(void)
{
	ft_lstclear(&g_shell.env, (t_lstdel)destroy_keyvalue);
	ft_lstclear(&g_shell.builtins, free);
	free(g_shell.wd);
	free_arr(g_shell.paths);
}
