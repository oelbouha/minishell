/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:26:33 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/16 18:12:10 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	get_token_len(char *line)
{
	static int	parentheses_count;
	int			len;

	len = 0;
	if (BONUS && (!ft_strncmp(line, "||", 2) || !ft_strncmp(line, "&&", 2)))
		len = 2;
	else if (BONUS && (line[0] == '(' || line[0] == ')'))
	{
		len = 1;
		parentheses_count += (line[0] == '(') - (line[0] == ')');
		if (parentheses_count < 0)
			return (-1);
	}
	else if (line[0] == '\''|| line[0] == '"')
		len = handle_quotes(line);
	else if (line[0] == '>' || line[0] == '<' || line[0] == '|')
		len = handle_redir_and_pipe(line);
	else
		len = simple_word(line);
	return (len);
}

char	*get_token(char *str, int *err)
{
	char	*token;
	int		len;

	len = get_token_len(str);
	if (len == 0)
		return (NULL);
	else if (len == -1)
	{
		*err = 3;
		len = 1;
	}
	token = ft_substr(str, 0, len);
	if (!token)
		*err = 1;
	return (token);
}

