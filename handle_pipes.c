/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:07:30 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/15 22:07:34 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_pipe_error(char **arr, char *line)
{
	if ((!arr[0] && check_pipes(line) == 1)
		|| count_pipes(arr) == 1
		|| check_pipes(line) == 1 || !arr[0])
		return (1);
	return (0);
}

int	check_pipes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (1);
	}
	return (0);
}

int	count_pipes(char **arr)
{
	int i;

	if (!arr[0] || !arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
