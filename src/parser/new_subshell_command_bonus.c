/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_subshell_command_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:57:36 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/12 16:01:35 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*new_subshell_command(t_list **start, t_cmd_exec_cond cond)
{
	t_list	*cmd_node;
	t_cmd	*cmd;

	cmd_node = ft_calloc(1, sizeof(t_list));
	if (cmd_node == NULL)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (free(cmd_node), NULL);
	cmd->type = COMPOUND_CMD;
	cmd->cond = cond;
	cmd->compound.subshell = TRUE;
	ft_lstdel_first(start, free);
	cmd->count = get_commands_count(*start);
	cmd->compound.arr = get_commands_arr(start, cmd->count);
	if (cmd->compound.arr == NULL)
		return (free(cmd_node), free(cmd), NULL);
	cmd_node->content = cmd;
	cmd_node->next = get_next_cmd(start);
	ft_lstdel_first(start, free);
	cmd->redirs = get_cmd_redirs(start);
	return (cmd_node);
}
