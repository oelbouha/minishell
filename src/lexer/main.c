/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:25:47 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/14 14:39:48 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(int c, char **v, char **env)
{
	char	*line;
	t_list	*l;
	(void)c;
	(void)v;
	setup(env);
	while (1)
	{
		line = read_line(0);
		if (line == NULL)
			return (0);
		l = tokenize(line);
		analyze(&l);
		print(l);
		free(line);
		ft_lstclear(&l, free);
	}
	return (0);
}
