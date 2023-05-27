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

int	skip_quotes(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	i++;
	return (i);
}

int	arr_length(char **arr)
{
	int	i;

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

int	should_expand_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && check_double_quote(&str[i], &i))
			return (1);
		else if (str[i] == '\'')
			i += skip_quotes(&str[i]);
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
	return (1);
}
