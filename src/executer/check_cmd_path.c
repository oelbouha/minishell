/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:03:12 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/18 15:03:28 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	check_cmd_path(char *cmd)
{
	DIR		*dir;

	if (ft_strchr(cmd, '/'))
	{
		dir = opendir(cmd);
		if (dir)
		{
			closedir (dir);
			print_error_msg(cmd, ": is a directory", 126);
		}
	}
	if (*cmd == '.' || ft_strchr(cmd, '/'))
	{
		if (access(cmd,  F_OK) < 0)
			print_error_msg(cmd, ": No such file or directory", 127);
		else if (access(cmd,  X_OK) < 0)
			print_error_msg(cmd, ": permission denied", 126);
	}
	return (1);
}