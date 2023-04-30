/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:26:18 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/30 13:26:20 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || str[i] == ' ' || str[i] == '"'
			|| str[i] == '\t' || str[i] == '\'')
			break ;
		i++;
	}
	return (ft_substr(str, 0, i));
}

int		get_len(char *str)
{
	char	*value;
	char	*key;
	int		len;

	len = 0;
	while (*str)
	{
		if (*str == '\'')
			while (++str && *str != '\'')
				len++;
		if (*str == '$' && *(str + 1) != '$')
		{
			key = get_key(++str);
			if (!key)
				return (-1);
			value = get_env_var(key);
			str += ft_strlen(key);
			len += ft_strlen(value);
			free(key);
			free(value);
		}
		else
		{
			str++;
			len++;
		}
	}
	return (len);
}

int	replace_var(char *new_str, char *str, int *i, int *j)
{
	char	*value;
	char	*key;

	key = get_key(str);
	if (!key)
		return (-1);
	value = get_env_var(key);
	ft_memmove(new_str, value, ft_strlen(value));
	*i += ft_strlen(key);
	*j += ft_strlen(value);
	free(key);
	free(value);
	return (0);
}

int	handle_double_quote(char *new_str, char *str, int *x, int *y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str[i++] = str[j++];
	while (str[j] && str[j] != '"')
	{
		if (str[j] == '$' && str[j + 1] != '$')
		{
			if (replace_var(&new_str[i], &str[++j], &j, &i) == -1)
				return (-1);
		}
		else
			new_str[i++] = str[j++];
	}
	*x += j;
	*y += i;
	return (0);
}

char	*expand_var(char *str)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;
	
	len = get_len(str);
	if (len == -1)
		return (NULL);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (handle_double_quote(&new_str[j], &str[i], &i, &j) == -1)
				return (free(new_str), NULL);
		}
		else if (str[i] == '\'')
		{
			new_str[j++] = str[i++];
			while (str[i] && str[i] != '\'')
				new_str[j++] = str[i++];
		}
		else if (str[i] == '$' && str[i + 1] != '$')
		{
			if (replace_var(&new_str[j], &str[++i], &i, &j) == -1)
				return (free(new_str), NULL);
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}