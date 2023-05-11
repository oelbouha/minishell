/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:26:44 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/03 21:41:46 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	simple_word_errors(t_list *lst)
{
	t_list *node;

	node = ft_lstlast(lst);
	if (node)
	{
		if (BONUS && ft_strcmp(node->content, ")") == 0)
			return (1);
	}
	return (0);
}

int	simple_word(char *str)
{
	char	next_quote;
	int		i;

	i = 0;
	while (str[i])
	{
		i += word_len(&str[i]);
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		{
			next_quote = str[i];
			while (str[++i] && str[i] != next_quote)
				;
			i++;
		}
		if (is_operator(&str[i]))
			break ;
	}
	return (i);
}


