/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:35:15 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/07 21:36:10 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	word_len(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == SPACE || str[i] == '>' || str[i] == '<'
			|| str[i] == '|' || str[i] == TAB
			|| str[i] == ')')
			return (i);
	}
	return (i);
}

int	handle_quotes(t_list **lst, char *str, int *err)
{
	char	*token;
	char	next_quote;
	int		i;

	i = 0;
	next_quote = str[i];
	while (str[++i] && str[i] != next_quote)
		;
	i++;
	i += word_len(&str[i]);
	token = ft_substr(str, 0, i);
	if (!token)
		*err = 1;
	ft_lstadd_back(lst, ft_lstnew(token));
	return (i);
}
