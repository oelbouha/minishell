/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:23:30 by oelbouha          #+#    #+#             */
/*   Updated: 2022/10/11 20:35:31 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(char *s, char c)
{
	int		i;
	int		count;
	char	k;
	char	*next_stop;

	count = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == 39 || s[i] == 34)
			k = s[i];
		else
			k = c;
		next_stop = ft_strchr(&s[i + 1], k);
		i += next_stop - &s[i];
		if (k != c)
			i += 2;
		count++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

int	word_len(char *str, char c)
{
	int 	len;
	int 	i;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == 39 || str[i] == 34 || str[i] == c)
			break ;
		len++;
	}
	return (len);
}

char	*single_and_double_quote(char *str, t_split *p)
{
	int		i;
	int		j;
	char	*new_str;
	char	next_stop_char;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != 32)
	{
		if (str[i] == 34 || str[i] == 39)
			next_stop_char = str[i];
		else
		{
			while (str[i] && (str[i] != 34 || str[i] != 39))
			{
				if (str[i] == 34 || str[i] == 39 || str[i] == 32)
					break ;
				new_str[j++] = str[i++];
			}
			if (str[i] == 32)
				break ;
		}
		i++;
		if (str[i] == next_stop_char)
			i++;
		else
		{
			while (str[i] && str[i] != next_stop_char)
				new_str[j++] = str[i++];
			i++;
		}
	}
	p->wordlen = i;
	new_str[j] = '\0';
	return (new_str);
}

char	**split_string(t_split *split, char c, char *s)
{
	while (s[split->i])
	{
		split->wordlen = 0;
		split->start = &s[split->i];
		if (s[split->i] == 39 || s[split->i] == 34)
		{
			split->str[split->j++] = single_and_double_quote(&s[split->i], split);
			split->i += split->wordlen;
		}
		else
		{
			split->wordlen = word_len(&s[split->i], c);
			split->i += split->wordlen;
			if (split->wordlen != 0)
				split->str[split->j++] = ft_substr(split->start, 0, split->wordlen);
		}
		while (s[split->i] && s[split->i] == c)
			split->i++;
	}
	split->str[split->j] = NULL;
	return (split->str);
}

char	**ft_split(char *s, char c)
{
	t_split	split;

	split.str = malloc((count(s, c) + 1) * sizeof(char *));
	if (!split.str)
		return (NULL);
	split.i = 0;
	while (s[split.i] && s[split.i] == c)
		split.i++;
	split.j = 0;
	return (split_string(&split, c, s));
}
/*
int main(int c, char **v)
{
	char **arr;

	// printf("str ==> %s\n", single_and_double_quote(v[1]));
	arr = ft_split(v[1], ' ');
	int i = -1;
	while (arr[++i])
		printf("arr ==> %s\n", arr[i]);
}*/