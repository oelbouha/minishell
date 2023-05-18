/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:05:57 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 10:17:04 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*new_command(t_list **head, t_cmd_exec_cond cond)
{
	t_list	*cmd;
	t_list	*first;
	int		count;

	first = *head;
	if (first == NULL)
		return (NULL);
	count = get_commands_count(first);
	cmd = NULL;
	if (count == 1)
		cmd = new_simple_command(head, cond);
	else
		cmd = new_compound_command(head, cond);
	return (cmd);
}

void	destroy_command(t_cmd *cmd)
{
	if (cmd->type == SIMPLE_CMD)
		destroy_simple_command(cmd);
	else if (cmd->type == COMPOUND_CMD)
		destroy_compound_command(cmd);
}
