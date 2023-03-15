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

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count = count + 1;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**ft_split_strings(char const *s, char c)
{
	int		i;
	int		x;
	int		wordlen;
	char	**strings;

	strings = (char **)malloc ((ft_count(s, c) + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	i = 0;
	x = 0;
	while (x < ft_count(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		wordlen = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			wordlen++;
		}
		strings[x] = ft_substr(s, i - wordlen, wordlen);
		x++;
	}
	strings[x] = NULL;
	return (strings);
}

char	**split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_split_strings(s, c));
}
