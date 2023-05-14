/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:40:23 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/14 16:11:49 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

// stts [byte1 byte2 byte3 byte4]

int	get_exit_status(pid_t pid)
{
	int				ret;
	unsigned char	*status;
	int				stts;

	stts = 0;
	waitpid(pid, &stts, 0);
	status = (unsigned char *) &stts;
	if (status[0])
		return (status[0] + 128);
	ret = (unsigned char) status[1];
	return (ret);
}
