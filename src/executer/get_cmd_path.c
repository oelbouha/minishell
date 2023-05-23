/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:55:59 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/20 13:10:17 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char	*make_cmd_path(char **path, char *cmd_name)
{
	char	*cmd_path;
	DIR		*dir;
	int		i;

	i = -1;
	cmd_path = NULL;
	cmd_name = ft_strjoin("/", cmd_name);
	if (cmd_name == NULL)
		exit (-1);
	while (path[++i] && *cmd_name)
	{
		cmd_path = ft_strjoin(path[i], cmd_name);
		if (cmd_path == NULL)
			return (free(cmd_name), exit (-1), NULL);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	free(cmd_name);
	dir = opendir(cmd_path);
	if (dir)
		return (free(cmd_path), closedir(dir), NULL);
	return (cmd_path);
}

char	*get_cmd_path(char *cmd_name)
{
	char	**shell_path;

	shell_path = get_path();
	if (shell_path == NULL && check_cmd_path(cmd_name))
		return (cmd_name);
	else if (ft_strchr(cmd_name, '/') && check_cmd_path(cmd_name))
		return (cmd_name);
	return (make_cmd_path(shell_path, cmd_name));
}
