/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_compound_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:57:36 by ysalmi            #+#    #+#             */
/*   Updated: 2023/04/16 23:40:04 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//		get the number of commands in a compound command
//	compound command is a pipeline "|" of simple or compound commands either
//	wraped in parentheses or not
//		-the commands count is the number of pipes plus 1
//		-only incerement if we are outside a compound command
//		-stop counting if encountered the closing parenthese
//		 or when there is no opening parenthese and find && or ||

int	get_compound_count(t_list *start, t_bool subshell)
{
	int	count;
	int	parentheses;

	parentheses = (subshell == TRUE);
	if (parentheses)
		start = start->next;
	count = 1;
	while (start)
	{
		if (ft_strcmp(start->content, "|") == 0 && (
			(subshell == FALSE && parentheses == 0)
			|| (subshell == TRUE && parentheses == 1)))
			count++;
		else if (ft_strcmp(start->content, "(") == 0)
			parentheses++;
		else if (ft_strcmp(start->content, ")") == 0 && --parentheses == 0)
				break ;
		else if (parentheses < 1  && BONUS
			&& ft_templatecmp(start->content, "&&:||", ':'))
			break ;
		start = start->next;
	}
	return (count);
}

t_list	*get_commands_arr(t_list *start, int count, t_bool subshell)
{
	t_list	*cmds;

	cmds = ft_calloc(count, sizeof(t_list));
	if (cmds == NULL)
		return (NULL);
	if (subshell)
		start = start->next;
	while (start)
	{
		
	}
	return (cmds);
}

t_cmd	*new_compound_command(t_list *start, t_cmd_exec_cond cond)
{
	t_cmd	*cmd;
	t_bool	subshell;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = COMPOUND_CMD;
	cmd->cond = cond;
	subshell = FALSE;
	if (ft_strcmp(start->content, "(") == 0)
		subshell = TRUE;
	cmd->compound.subshell = subshell;
	cmd->count = get_compound_count(start, cmd->compound.subshell);
	cmd->compound.cmds = get_commands_arr(start, cmd->count, subshell);
	return (cmd);
}
