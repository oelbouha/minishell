/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:30:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/11 17:11:06 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "lexer.h"
#include "parser.h"

int	main(void)
{
	char	*line;
	t_list	*tokens;
	t_list	*command;
	int		err;

	while (1)
	{
		ft_printf("stts: %d\n", get_last_status());
		line = read_line(1);
		if (line == NULL)
			return (get_last_status());
		tokens = tokenize(line);
		err = analyze(&tokens);
		print(tokens);
		(void)command;
		free(line);
		set_last_status(get_last_status() + 1);
	}
}
