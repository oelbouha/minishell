/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:13:39 by ysalmi            #+#    #+#             */
/*   Updated: 2023/03/23 16:40:01 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	configure_readline(void)
{
	return ;
}

char	*get_prompt(void)
{
	char	*prompt;

	prompt = ft_strjoin("ysalmi ", "\x1b[34;01mminishell $\x1b[32;01m〉\x1b[0m");
	return (prompt);
}

/*
 *		Description
 *
 *	@params:
 *		@state: indicate if it's the first call to the function (state = 0)
 *	
 *	@return:
 *		returns the line read
 */

char	*get_input(t_ull state)
{
	char	*line;
	char	*prompt;

	if (state == 0)
		configure_readline();
	prompt = get_prompt();
	line = readline(prompt);
	return (line);
}

int	main(void)
{
	char *line = get_input(0);
	printf("%s\n", line);
	return (0);
}
