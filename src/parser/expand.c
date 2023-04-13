/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:41:08 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/12 23:23:12 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

char	*remove_quotes(char *arg)
{
	char	*str;
	char	c;

	str = arg;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			c = *str;
			ft_memmove(str, str + 1, ft_strlen(str));
			str = ft_strchr(str, c);
			ft_memmove(str, str + 1, ft_strlen(str));
		}
		else
			str++;
	}
	return (arg);
}
