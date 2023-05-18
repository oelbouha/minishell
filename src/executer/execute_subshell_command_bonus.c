/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell_command_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:53:49 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 11:32:49 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

/*

if (subshell)
	prep_redirs
	fork
	loop and execute
	wait for last cmd status
	wait for the rest
	return status

else
	loop and execute
	wait for last cmd status
	wait for the rest
	return status


*/

int	execute_subshell_command(t_cmd *cmd, t_bool wait_child)
{
	pid_t			pid;
	int				status;

	pid = fork();
	if (pid)
	{
		if (wait_child)
			return (get_exit_status(pid));
		return (pid);
	}		
	prep_redirs(cmd->redirs);
	status = execute(cmd->data.lst);
	exit(status);
	return (status);
}