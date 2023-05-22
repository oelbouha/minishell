/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:34:55 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/19 19:08:03 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	read_heredoc(char *limiter)
{
	char	*line;
	int		fds[2];

	if (pipe(fds))
		return (-1);
	remove_quotes(limiter);
	while (has_been_interupted() == 0)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fds[1]);
		ft_putstr_fd("\n", fds[1]);
		free(line);
	}
	close(fds[1]);
	return (fds[0]);
}
