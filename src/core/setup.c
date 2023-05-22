/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:21:05 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/22 16:07:25 by ysalmi           ###   ########.fr       */
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

void	setup_sighandler(void)
{
	struct sigaction	act;

	act.sa_handler = sig_int_handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
}

int	getc(FILE *stream)
{
	int		res;
	char	c;

	(void)stream;
	errno = 0;
	res = read(0, &c, sizeof(unsigned char));
	if (res == 0 || errno == EINTR)
		return (EOF);
	return (c);
}
/*
 *
 *	handle error properly when get_current_wd() returns NULL
 * 
 */

int	setup(char *env[])
{
	char	*path;

	g_shell.env = new_dictionary(env, '=');
	if (g_shell.env == NULL)
		return (1);
	g_shell.builtins = construct_builtins_list();
	if (g_shell.builtins == NULL)
		return (ft_lstclear(&g_shell.env, (t_lstdel)destroy_keyvalue), 1);
	g_shell.wd = getcwd(NULL, 0);
	if (g_shell.wd == NULL)
		return (1);
	path = get_env_var("PATH");
	if (path == NULL)
	{
		set_env_var("PATH","/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		path = get_env_var("PATH");
	}// if path is still NULL return (1);
	g_shell.paths = ft_split(path, ':');
	free(path);
	//setup_sighandler();
	signal(SIGINT, sig_int_handler);
	g_shell.last_stts = 0;
	//rl_getc_function = getc;
	return (0);
}

int	get_state(void)
{
	return (g_shell.state);
}

void	set_state(int value)
{
	g_shell.state = value;
}
