/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:35:15 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/08 13:57:16 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_quotes(char *line)
{
	int		i;
	char	*ptr;
	char	*start;
	char	next_quote;

	i = 0;
	while (line[i])
	{
		start = &line[i];
		if (line[i] == 34 || line[i] == 39)
		{
			next_quote = line[i];
			i++;
			if (!ft_strchr(&line[i], next_quote))
				return (1);
			ptr = ft_strchr(&line[i], next_quote);
			i += ptr - start;
		}
		else
			i++;
	}
	return (0);
}

int	handle_quotes(char *str)
{
	char	next_quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		{
			next_quote = str[i];
			while (str[++i] && str[i] != next_quote)
				;
			i++;
		}
		if (is_operator(str[i], str[i + 1]))
			break ;
		i += word_len(&str[i]);
	}
	return (i);
}
