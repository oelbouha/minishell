/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:31:10 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/09 15:26:50 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_error_msg(char *token)
{
	printf("%s\n", ft_strjoin("minishell: syntax error near unexpected token ", token));
}

int		is_and_or(char *str)
{
	if (ft_strncmp(str, "||", 2) == 0 || ft_strncmp(str, "&&", 2) == 0)
		return (1);
	return (0);
}

int		is_operator(char c, char s)
{
	if (ft_strchr(" ><|\t", c))
		return (1);
	else if (BONUS && ((c == ')' || c == '(') || (c == '&' && s == '&')))
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
