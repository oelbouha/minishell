/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:08:19 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/11 22:08:22 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	should_expand_wildcard(char *line)
{
	if (ft_templatecmp(line, "'\"/", ':'))
		return (0);
	else if (ft_strchr(line, '*'))
		return (1);
	return (0);
}

int	arr_length(char **arr)
{
	int	i;

	if (arr == NULL)
		return (0);
	i = -1;
	while (arr[++i])
		;
	return (i);
}

int	check_double_quote(char *str, int *i)
{
	char	quote;
	int		j;

	j = 0;
	quote = str[j];
	j++;
	while (str[j] && str[j] != quote)
	{
		if (str[j] == '$')
			return (1);
		j++;
	}
	j++;
	*i += j;
	return (0);
}

int	should_expand(char *str)
{
	char	quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (check_double_quote(&str[i], &i))
				return (1);
		}
		else if (str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			i++;
		}
		else if (str[i] == '$')
			return (1);
		else
			i++;
	}
	return (0);
}

int	needs_spliting(char *str)
{
	if (ft_strchr(str, '"') || ft_strchr(str, '\''))
		return (0);
	else
		return (1);
}
