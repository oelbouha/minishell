/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:09:33 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/12 13:09:51 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char **arr, char *path, char **env)
{

	if (!arr[0])
		print_error_msg(arr[0], ": command not found", 127, arr);
	if (path || ft_search(arr[0], '/') || arr[0][0] == '/'
		|| arr[0][0] == '.')
	{
		if (check_path(arr[0]) == 0)
			path = arr[0];
		if (execve(path, arr, env) == -1)
		{
			perror("minishell: execve");
			exit (1);
		}
	}
	else
		print_error_msg(arr[0], ": command not found", 127, arr);
}