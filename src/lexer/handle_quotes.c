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

int	handle_quotes(t_list **lst, char *str, int *err)
{
	char	*token;
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
	token = ft_substr(str, 0, i);
	if (!token)
	{
		*err = 1;
		return (1);
	}
	ft_lstadd_back(lst, ft_lstnew(token));
	return (i);
}
