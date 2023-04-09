/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:31:10 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/08 15:54:04 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		is_operator(char c, char s)
{
	if (c == ' ' || c == '>' || c == '<'
		|| c == '|' || c == '\t')
		return (1);
	else if (BONUS && (c == ')' || c == '(') || (c == '&' && s == '&'))
		return (1);
	return (0);
}

int	word_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '>' || str[i] == '<'
			|| str[i] == '|' || str[i] == '\t' || str[i] == 39 || str[i] == 34)
			return (i);
		else if (BONUS && (str[i] == ')' || str[i] == '('
			|| !ft_strncmp(&str[i], "&&", 2)))
			return (i);
		i++;
	}
	return (i);
}
