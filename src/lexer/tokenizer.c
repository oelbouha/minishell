/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:16:56 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/10 18:27:16 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	get_word_length(const char *line)
{
	int		length;
	char	*res;

	length = 0;
	while (line[length])
	{
		if (line[length] == '"' || line[length] == '\'')
		{
			res = ft_strchr(&line[length + 1], line[length]);
			if (res == NULL)
			{
				res = ft_strchr(line, '\0');
				length += res - &line[length];
				return (length);
			}
			length += res - &line[length] + 1;
		}
		else if (is_word_delimiter(&line[length]))
			break ;
		else
			length++;
	}
	return (length);
}

char	*skip_spaces(const char *line)
{
	char	*ret;

	ret = (char *)line;
	while (*ret && (*ret == ' ' || *ret == '\t'))
		ret++;
	return (ret);
}

t_list	*new_token(const char *line, int length)
{
	t_list	*token;
	char	*content;

	content = ft_substr(line, 0, length);
	if (content == NULL)
		return (NULL);
	token = ft_lstnew(content);
	if (token == NULL)
		free(content);
	return (token);
}

t_list	*tokenize(const char *line)
{
	t_list	*tokens;
	t_list	*token;
	int		length;

	tokens = NULL;
	line = skip_spaces(line);
	while (*line)
	{
		length = get_token_length(line);
		token = new_token(line, length);
		if (token == NULL)
			return (ft_lstclear(&tokens, free), NULL);
		ft_lstadd_back(&tokens, token);
		line = skip_spaces(line + length);
	}
	return (tokens);
}
