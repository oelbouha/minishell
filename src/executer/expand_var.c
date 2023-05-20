/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:26:18 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/09 15:30:51 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	is_invalid_key(const char *key)
{
	return (!(ft_isalpha(*key) || ft_strchr("$?_@", *key) || ft_isdigit(*key)));
}

int	get_expanded_length(char *str)
{
	char	*key;
	int		len;

	len = 0;
	while (*str)
	{
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

int	replace_var(char *expanded, char *str, int *i, int *j)
{
	char	*key;
	char	*value;

	if ((*str == 0 || is_invalid_key(str)) && ++(*j))
		*expanded = '$';
	else
	{
		key = get_key(str);
		if (!key)
			return (-1);
		value = get_env_var(key);
		if (value)
		{
			ft_memmove(expanded, value, ft_strlen(value));
			*j += ft_strlen(value);
		}
		*i += ft_strlen(key);
		return (free(key), free(value), 0);
	}
	return (0);
}

char	*expand_var(char *str)
{
	char	*expanded;
	int		len;
	int		i;
	int		j;

	len = get_expanded_length(str);
	expanded = malloc(len + 1);
	if (expanded == NULL || len == -1)
		return (free(expanded), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (replace_var(&expanded[j], &str[++i], &i, &j) == -1)
				return (free(expanded), NULL);
		}
		else
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}
