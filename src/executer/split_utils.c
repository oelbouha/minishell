/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:13:03 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/11 22:13:06 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

int	quotes_len(char *str)
{
	char	next_quote;
	int		i;

	i = 0;
	next_quote = str[i];
	while (str[++i] && str[i] != next_quote)
		;
	i++;
	return (i);
}

int	get_key_len(char *str)
{
	int		i;

	i = 1;
	while (str[i] && str[i] == '$')
		i++;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}
