/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:34:55 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/22 15:40:59 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	hgetc(FILE *stream)
{
	int		res;
	char	c;

	(void)stream;
	errno = 0;
	res = read(0, &c, sizeof(unsigned char));
	if (res == 0 || errno == EINTR)
		return (EOF);
	return (c);
}

int	read_heredoc(char *limiter)
{
	char	*line;
	int		fds[2];
	void	*ptr;

	if (pipe(fds))
		return (-1);
	set_state(2);
	remove_quotes(limiter);
	ptr = rl_getc_function;
	rl_getc_function = hgetc;
	while (get_state() == 2)
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
	if (get_state() == 2)
		set_state(0);
	rl_getc_function = ptr;
	return (fds[0]);
}
