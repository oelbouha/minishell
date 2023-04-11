/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_last_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:46:03 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/11 15:20:49 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_internal.h"

int	set_last_status(unsigned char status)
{
	g_shell.last_stts = status;
	return (0);
}
