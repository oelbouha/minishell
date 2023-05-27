/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_subshell_command_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:57:36 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/18 10:36:08 by ysalmi           ###   ########.fr       */
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
	cmd->type = SUBSHELL_CMD;
	cmd->cond = cond;
	ft_lstdel_first(start, free);
	cmd->count = get_commands_count(*start);
	cmd->data.lst = new_command(start, NONE);
	if (cmd->data.lst == NULL)
		return (free(cmd_node), free(cmd), NULL);
	cmd_node->content = cmd;
	ft_lstdel_first(start, free);
	cmd->redirs = get_cmd_redirs(start);
	return (cmd_node);
}

void	destroy_subshell_command(t_cmd *cmd)
{
	ft_lstclear(&cmd->data.lst, (t_lstdel)destroy_command);
	if (cmd->redirs && cmd->redirs != (t_list *)-1)
		ft_lstclear(&cmd->redirs, (t_lstdel)destroy_redir);
	free(cmd);
}
