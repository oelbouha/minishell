/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:25:47 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/06 21:41:33 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
t_list	*tokenize(const char *line);

int	main(void)
{
	t_list *l;
	while (1)
	{
		char *line = readline("Lexer:$ ");
		add_history(line);
		l = tokenize(line);
		print(l);
	}
	return (0);
}
