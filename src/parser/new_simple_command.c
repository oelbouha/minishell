/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:41:15 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/30 15:29:38 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_cmd_args_count(t_list *start)
{
	int	count;

	count = 0;
	while (start)
	{
		if (is_redirection(start->content))
			start = start->next;
		else if (is_an_operator(start->content))
			break ;
		else
			count++;
		start = start->next;
	}
	return (count);
}

t_list	*get_cmd_args_list(t_list **head, int count)
{
	t_list	*args;
	t_list	*start;
	t_list	*prev;

	args = NULL;
	prev = NULL;
	start = *head;
	while (start && count > 0)
	{
		if (is_redirection(start->content))
		{
			if (prev == NULL)
				*head = start;
			prev = start->next;
			start = start->next->next;
		}
		else if (is_an_operator(start->content))
			break ;
		else
			start = move_node(&args, start, prev);
	}
	if (prev == NULL)
		*head = start;
	return (args);
}

t_list	*new_simple_command(t_list **start, t_cmd_exec_cond cond)
{
	t_list	*cmd_node;
	t_cmd	*cmd;

	cmd_node = ft_calloc(1, sizeof(t_list));
	if (cmd_node == NULL)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (free(cmd_node), NULL);
	cmd->type = SIMPLE_CMD;
	cmd->cond = cond;
	cmd->count = get_cmd_args_count(*start);
	cmd->simple.args = get_cmd_args_list(start, cmd->count);
	if (cmd->count && cmd->simple.args == NULL)
		return (free(cmd_node), free(cmd), NULL);
	cmd->redirs = get_cmd_redirs(start);
	if (cmd->redirs == NULL)
		return (free(cmd_node), destroy_simple_command(cmd), NULL);
	cmd_node->content = cmd;
	return (cmd_node);
}

void	destroy_simple_command(t_cmd *cmd)
{
	ft_lstclear(&cmd->simple.args, free);
	if (cmd->redirs != NO_REDIRS)
		ft_lstclear(&cmd->redirs, (t_lstdel)destroy_redir);
	free(cmd);
}
