/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:26:18 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/01 18:06:21 by ysalmi           ###   ########.fr       */
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

int		get_length(char *str)
{
	char	*value;
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

	if (*str == '$')
		*i += 1;
	else if (*str == 0)
	{
		new_str[0] = '$';
		*j += 1;
	}
	else
	{
		key = get_key(str);
		if (!key)
			return (-1);
		value = get_env_var(key);
		ft_memmove(new_str, value, ft_strlen(value));
		*i += ft_strlen(key);
		*j += ft_strlen(value);
		free(key);
		free(value);
	}
	return (0);
}

int	handle_double_quote(char *expanded, char *str, int *x, int *y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	expanded[j++] = str[i++];
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '$')
		{
			if (str[++i] == '"' || str[i] == '\'')
				expanded[j++] = '$';
			if (replace_var(&expanded[j], &str[i], &i, &j) == -1)
				return (-1);
		}
		else
			expanded[j++] = str[i++];
	}
	expanded[j++] = str[i++];
	*x += i;
	*y += j;
	return (0);
}

void	handle_single_quote(char *expanded, char *str, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	expanded[j++] = str[i++];
	while (str[i] && str[i] != '\'')
		expanded[j++] = str[i++];
	if (str[i])
		expanded[j++] = str[i++];
	*x += i;
	*y += j;
}

char	*expand_var(char *str)
{
	char	*expanded;
	int		len;
	int		err;
	int		i;
	int		j;
	
	len = get_length(str);
	expanded = malloc(len + 1);
	if (expanded == NULL || len == -1)
		return (free(expanded), NULL);
	err = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"')
			err = handle_double_quote(&expanded[j], &str[i], &i, &j);
		else if (str[i] == '\'')
			handle_single_quote(&expanded[j], &str[i], &i, &j);
		else if (str[i] == '$')
			err = replace_var(&expanded[j], &str[++i], &i, &j);
		else
			expanded[j++] = str[i++];
		if (err)
				return (free(expanded), NULL);
	}
	expanded[j] = '\0';
	return (expanded);
}
