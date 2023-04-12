/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:52:09 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/12 15:26:02 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

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

void	cd_substitute(char *wd, char *sub)
{
	char	**names;
	char	*str;
	int		i;

	names = ft_split(sub, '/');
	i = -1;
	while (names[++i])
	{
		str = ft_stristr(wd, names[i]);
		if (str)
			ft_memcpy(str, names[i], ft_strlen(names[i]));
		free(names[i]);
	}
	free(names);
}

int	cd_path(char *path)
{
	char	*to;
	int		err;

	to = path;
	if (ft_issubset("/", to))
		to = "/";
	err = chdir(to);
	if (err)
		return (msh_log("cd", strerror(errno), "", FALSE), 1);
	free(g_shell.wd);
	if (ft_strcmp(path, "//") == 0)
		g_shell.wd = ft_strdup("//");
	else
	{
		g_shell.wd = getcwd(NULL, 0);
		if (g_shell.wd == NULL)
			return (msh_log("cd", strerror(errno), "", FALSE), 1);
		cd_substitute(g_shell.wd, to);
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
