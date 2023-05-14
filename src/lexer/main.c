/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:25:47 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/11 18:21:51 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(void)
{
	char	*line;
	t_list	*l;

	while (1)
	{
		line = read_line(0);
		if (line == NULL)
			return (0);
		l = tokenize(line);
		analyze(&l);
		if (l)
			print(l);
		free(line);
		ft_lstclear(&l, free);
	}
	return (0);
}
