/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:25:47 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/08 14:25:58 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(void)
{
	t_list *l;
	while (1)
	{
		char *line = readline("Lexer:$ ");
		add_history(line);
		l = split_line(line);
		print(l);
	}
	return (0);
}