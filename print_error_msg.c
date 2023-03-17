/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:15:00 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/12 13:15:15 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	print_error_msg(char *str, char *msg, int exit_status, char **arr)
{
	char	*ptr;
	char	*s;

	ptr = ft_strjoin("minishell: ", str);
	s = ft_strjoin(ptr, msg);
	ft_putstr_fd(s, 2);
	write (2, "\n", 1);
	free(s);
	free(ptr);
	if (arr)
		ft_free(arr);
	exit (exit_status);
}

void	parse_error()
{
	int		pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		exit (1);
	}
	if (pid == 0)
	{
		ft_putstr_fd("minishell: parse error\n", 2);
		exit (130);
	}
}