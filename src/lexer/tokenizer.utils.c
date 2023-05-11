/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:16:56 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/10 10:08:18 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_word_delimiter(const char *line)
{
	if (ft_strchr(" \t|<>", *line))
		return (1);
	return (0);
}

int	get_token_length(const char *line)
{
	if (ft_strncmp(line, ">>", 2) == 0 || ft_strncmp(line, "<<", 2) == 0)
		return (2);
	else if (ft_strchr("<>|", *line))
		return (1);
	else
		return (get_word_length(line));
}
