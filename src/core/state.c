/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:17:00 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/26 15:52:20 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	get_state(void)
{
	return (g_shell.state);
}

int	set_state(int value)
{
	g_shell.state = value;
	return (1);
}
