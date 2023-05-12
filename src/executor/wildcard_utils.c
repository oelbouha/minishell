/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:08:45 by oelbouha          #+#    #+#             */
/*   Updated: 2023/05/11 22:08:49 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

int	should_expand_wildcard(char *line)
{
	if (ft_templatecmp(line, "'\"/", ':'))
		return (0);
	else if (ft_strchr(line, '*'))
		return (1);
	return (0);
}

int	get_length(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}
