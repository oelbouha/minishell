/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:47:39 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/14 13:25:15 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	execute_compound_command(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}

int	execute(t_list *cmd_node)
{
	t_cmd	*cmd;
	int		status;

	while (cmd_node)
	{
		cmd = cmd_node->content;
		if (cmd->type == SIMPLE_CMD)
			status = execute_simple_command(cmd, FALSE, TRUE);
		else
			status = execute_compound_command(cmd);
		set_last_status(status);
		cmd_node = cmd_node->next;
	}
	return (status);
}
