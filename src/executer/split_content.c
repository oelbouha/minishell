/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:08:08 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/11 22:08:13 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	simple_word_len(char *str)
{
	char	next_quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			next_quote = str[i];
			while (str[++i] && str[i] != next_quote)
				;
			i++;
			return (i);
		}
		else if (str[i] == '$')
			return (i);
		else
			i++;
	}
	return (i);
}

int	get_token_len(char *line)
{
	int		len;

	len = 0;
	if (line[0] == '\'' || line[0] == '"')
		len = quotes_len(line);
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
