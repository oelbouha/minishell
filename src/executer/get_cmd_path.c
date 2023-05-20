/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:55:59 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/20 12:42:31 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char	*get_cmd_path(char *cmd_name)
{
	char	**path;
	char	*cmd_path;
	char	*str;
	int		i;

	path = get_path();
	// check access == 0
	// return (cmd_name)
	if (ft_strchr(cmd_name, '/'))
		return (cmd_name);
	if (ft_strchr(cmd_name, '/') || *cmd_name == '.')
	{
		if (check_cmd_path(cmd_name))
			return (cmd_name);
	}
	i = -1;
	while (path[++i] && *cmd_name)
	{
		str = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(str, cmd_name);
		free(str);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}
