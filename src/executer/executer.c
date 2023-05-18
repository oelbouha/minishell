/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:47:39 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 11:34:48 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	should_execute(t_cmd_exec_cond cond, int status)
{
	if (cond == NONE)
		return (1);
	else if (status == 0 && cond == AND)
		return (1);
	else if (status != 0 && cond == OR)
		return (1);
	else
		return (0);
}

int	execute(t_list *cmd_node)
{
	t_cmd	*cmd;
	int		status;

	status = get_last_status();
	while (cmd_node)
	{
		cmd = cmd_node->content;
		if (should_execute(cmd->cond, status))
		{
			if (cmd->type == SIMPLE_CMD)
				status = execute_simple_command(cmd, FALSE, TRUE);
			else if (cmd->type == COMPOUND_CMD)
				status = execute_compound_command(cmd);
			else
				status = execute_subshell_command(cmd, TRUE);
			set_last_status(status);
		}
		cmd_node = cmd_node->next;
	}
	return (status);
}
