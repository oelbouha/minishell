/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:25:47 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/11 13:24:13 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(void)
{
	t_list *l;
	while (1)
	{
		char *line = read_line(0);
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
