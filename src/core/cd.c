/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/11 23:19:50 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

/*
 *	check if str is a subset of set
 */

int	is_subset(char *set, char *str)
{
	int	i;
	int	j;
	int	present;

	i = -1;
	while (str[++i])
	{
		present = 0;
		j = -1;
		while (set[++j])
			if (set[j] == str[i])
				present = 1;
		if (present == 0)
			return (0);
	}
	return (1);
}

int	cd_home(void)
{
	char	*to;
	int		err;

	to = get_env_var("HOME");
	if (to == NULL)
	{
		msh_log("cd", "HOME not set", "", FALSE);
		return (1);
	}
	err = chdir(to);
	free(to);
	if (err)
	{
		msh_log("cd", strerror(errno), "", FALSE);
		return (1);
	}
	free(g_shell.wd);
	g_shell.wd = getcwd(NULL, 0);
	if (g_shell.wd == NULL)
	{
		msh_log("cd", strerror(errno), "", FALSE);
		return (1);
	}
	return (0);
}

int	cd_path(char *path)
{
	char	*to;
	int		err;

	to = path;
	if (is_subset("/", to))
		to = "/";
	err = chdir(to);
	if (err)
	{
		msh_log("cd", strerror(errno), "", FALSE);
		return (1);
	}
	free(g_shell.wd);
	if (ft_strcmp(path, "//") == 0)
		g_shell.wd = ft_strdup("//");
	else
	{
		g_shell.wd = getcwd(NULL, 0);
		if (g_shell.wd == NULL)
		{
			msh_log("cd", strerror(errno), "", FALSE);
			return (1);
		}
	}
	return (0);
}

int	cd(int c, char **v)
{
	int	ret;

	if (c == 1)
		ret = cd_home();
	else
		ret = cd_path(v[1]);
	return (ret);
}
