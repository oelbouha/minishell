/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:12:04 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/11 15:14:43 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_bonus.h"

int	is_an_operator(const char *token)
{
	return (ft_templatecmp(token, OPERATORS, ':'));
}
