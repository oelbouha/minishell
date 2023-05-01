/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:05:57 by ysalmi            #+#    #+#             */
/*   Updated: 2023/05/01 09:51:09 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*get_next_cmd(t_list **head)
{
	t_list	*cmd;
	t_list	*operator;
	t_list	*start;

	operator = *head;
	cmd = NULL;
	if (operator == NULL)
		return (NULL);
	start = operator->next;
	if (ft_strcmp(operator->content, "&&") == 0)
		cmd = new_command(&start, AND);
	else if (ft_strcmp(operator->content, "||") == 0)
		cmd = new_command(&start, OR);
	ft_lstdelone(operator, free);
	*head = start;
	return (cmd);
}

t_list	*new_command(t_list **head, t_cmd_exec_cond cond)
{
	t_list	*cmd;
	t_bool	subshell;
	t_list	*first;
	int		count;

	first = *head;
	count = get_commands_count(first);
	subshell = FALSE;
	cmd = NULL;
	if (count == 1 && ft_strcmp(first->content, "("))
		cmd = new_simple_command(head, cond);
	else
	{
		if (count == 1 && ft_strcmp(first->content, "(") == 0)
		{
			*head = first->next;
			ft_lstdelone(first, free);
			subshell = TRUE;
		}
		cmd = new_compound_command(head, cond);
		((t_cmd *)cmd->content)->compound.subshell = subshell;
	}
	cmd->next = get_next_cmd(head);
	return (cmd);
}

void	destroy_command(t_cmd *cmd)
{
	if (cmd->type == SIMPLE_CMD)
		destroy_simple_command(cmd);
	else if (cmd->type == COMPOUND_CMD)
		destroy_compound_command(cmd);
}
