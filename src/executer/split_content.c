/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:08:08 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/26 18:43:24 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	simple_word_len(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i += skip_quotes(&str[i]);
		else if (str[i] == '$')
			return (i);
		else
			i++;
	}
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

int	get_token_len(char *line)
{
	int		len;

	len = 0;
	if (line[0] == '\'' || line[0] == '"')
		len = ft_strchr(line + 1, *line) - line + 1;
	else if (*line == '$')
		len = get_key_len(line);
	else
		len = simple_word_len(line);
	return (len);
}

t_list	*create_token(char *str)
{
	t_list	*node;
	char	*token;
	int		len;

	len = get_token_len(str);
	if (len == 0)
		return (NULL);
	token = ft_substr(str, 0, len);
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		return (NULL);
	}
	return (node);
}

t_list	*split_content(char *line)
{
	t_list	*lst;
	t_list	*token;
	int		i;

	lst = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		token = create_token(&line[i]);
		if (token == NULL)
			return (ft_lstclear(&lst, free), NULL);
		ft_lstadd_back(&lst, token);
		i += ft_strlen(token->content);
	}
	return (lst);
}
