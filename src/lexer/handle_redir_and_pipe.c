/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_and_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:36:58 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/07 21:37:18 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_redir_and_pipe(char *str)
{
	char	next_char;
	int		i;

	i = 0;
	next_char = str[i];
	if (next_char == '|')
		return (1);
	if (str[i + 1] == next_char)
		i = 2;
	else
		i = 1;
	return (i);
}

