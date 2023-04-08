/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:26:44 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/08 18:26:47 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	simple_word(t_list **lst, char *str, int *err)
{
	char	*token;
	char	next_quote;
	int		i;

	i = 0;
	while (str[i])
	{
		i += word_len(str);
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		{
			next_quote = str[i];
			while (str[++i] && str[i] != next_quote)
				;
			i++;
		}
		if (is_operator(str[i], str[i + 1]))
			break ;
	}
	token = ft_substr(str, 0, i);
	if (!token)
	{
		*err = 1;
		return (i);
	}
	ft_lstadd_back(lst, ft_lstnew(token));
	return (i);
}