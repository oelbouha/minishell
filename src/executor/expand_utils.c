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

#include "../parser/parser.h"

int	should_expand_var(char *str)
{
	char	quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
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
	if (ft_strchr(str, '"') || ft_strchr(str, '\'') || !should_expand_var(str))
		return (0);
	else
		return (1);
}

int	is_invalid_key(const char *key)
{
	return (!(ft_isalpha(*key) || ft_strchr("$?_", *key) || ft_isdigit(*key)));
}

int	get_expanded_length(char *str)
{
	char	*key;
	int		len;

	len = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			while (++str && *str != '\'')
				len++;
			len += 2;
		}
		if (*str == '$' && !(str[1] == 0 || is_invalid_key(str + 1)))
		{
			key = get_key(++str);
			if (!key)
				return (-1);
			str += ft_strlen(key);
			len += get_env_var_len(key);
			free(key);
		}
		else if (str++)
			len++;
	}
	return (len);
}

char	*get_key(char *str)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(*str) || *str == '_'))
		return (ft_substr(str, 0, i));
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			break ;
		i++;
	}
	return (ft_substr(str, 0, i));
}
