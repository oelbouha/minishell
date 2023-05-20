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

char	*get_cmd_path(char *cmd_name)
{
	char	**path;
	char	*cmd_path;
	DIR		*dir;
	int		i;

	path = get_path();
	if (ft_strchr(cmd_name, '/'))
		if (check_cmd_path(cmd_name))
			return (cmd_name);
	cmd_name = ft_strjoin("/", cmd_name);
	i = -1;
	while (path[++i] && *cmd_name)
	{
		cmd_path = ft_strjoin(path[i], cmd_name);
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
