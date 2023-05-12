/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fd_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:25:34 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/30 13:25:39 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

int	change_var(char *line, int fd, int *i)
{
	char	*value;
	char	*key;

	if (*line == '$')
		*i += 1;
	else if (*line == '\n' || *line == 0 || is_invalid_key(line))
		ft_putchar_fd('$', fd);
	else
	{
		key = get_key(line);
		if (!key)
			return (-1);
		value = get_env_var(key);
		ft_putstr_fd(value, fd);
		*i += ft_strlen(key);
		free(value);
		free(key);
	}
	return (0);
}

int	replace_var_with_value(char *line, int fd)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			change_var(&line[++i], fd, &i);
		else
			ft_putchar_fd(line[i++], fd);
	}
	return (0);
}

int	expand_heredoc(int fd)
{
	int		pipe1[2];
	char	*line;

	if (pipe(pipe1) < 0)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '$'))
		{
			if (replace_var_with_value(line, pipe1[1]) == -1)
				return (free(line), -1);
		}
		else
			ft_putstr_fd(line, pipe1[1]);
		free(line);
	}
	close (fd);
	close (pipe1[1]);
	return (pipe1[0]);
}
