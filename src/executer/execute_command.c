/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:47:39 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/23 20:34:30 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	execute_command(t_cmd *cmd, t_bool force_fork, t_bool wait_child)
{
	int	ret;

	if (cmd->type == SIMPLE_CMD)
		ret = execute_simple_command(cmd, force_fork, wait_child);
	else
		ret = execute_compound_command(cmd);
	return (ret);
}

