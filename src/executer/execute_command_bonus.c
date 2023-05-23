/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:32:36 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/23 20:33:07 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_bonus.h"

int	execute_command(t_cmd *cmd, t_bool force_fork, t_bool wait_child)
{
	int	ret;

	if (cmd->type == SIMPLE_CMD)
		ret = execute_simple_command(cmd, force_fork, wait_child);
	else if (cmd->type == COMPOUND_CMD)
		ret = execute_compound_command(cmd);
	else
		ret = execute_subshell_command(cmd, wait_child);
	return (ret);
}
